# swig文档：https://www.swig.org/Doc4.2/SWIGDocumentation.pdf
# swig源码：https://github.com/swig/swig/tree/master

import os
import shutil

import sys


# 获取当前脚本的目录
current_dir = os.path.dirname(os.path.abspath(__file__))
# 构造 utils 目录的路径
utils_dir = os.path.join(current_dir, 'utils')
# 将 utils 目录添加到 Python 的模块搜索路径
sys.path.append(current_dir)
sys.path.append(utils_dir)


from utils.code_generate_utils import (
    swig_config_dir,
    java_gen_code_build_dir,
    java_gen_code_src_dir,
    cpp_gen_code_dir,
    bridge_android_sdk_dir,
    package_common_pre,
    package_common_pre_path,
    swig_interface_black_list,
    common_swig_config_path,
    common_cpp_headers,
    swig_gen_common_code_line_start,
    swig_gen_common_code_line_end,
    ExpressionParseProcessInfo,
    ExpressionParseResult,
)
from utils import file_utils, git_utils, code_generate_utils
from utils.file_utils import (ReplaceInfo)


class DuplicateFileNameError(Exception):
    """自定义异常，用于重复文件名"""

    pass


class SwigConfigFileInfo:

    # swig 配置文件名称
    interface_name: str

    # swig 配置文件路径
    interface_path: str

    # jni 桥接类名
    jniclassName: str = None

    # jni 桥接类的 package_name
    jniclasspackage: str = None

    # 独立命名空间名
    namespace_name: str = None

    # java类package_name：key=类名，value=package_name
    class_to_package: dict[str, str]

    # 生成的 .cxx 文件的路径
    cxx_file_path: str

    # 生成的 .java 文件的目录
    java_code_outdir: str

    # 依赖的其他 swig 配置，存储配置文件名
    import_swig_configs: list[str]

    def __init__(self):
        return


# 脚本总入口，生成桥接代码
def generate_code():
    # 1. 找到所有的 swig 配置文件，并记录路径信息
    swig_filename_to_path = find_swig_config_file(swig_config_dir)

    # 2. 删除上次生成的文件
    file_utils.remove_dir_and_contents(java_gen_code_build_dir)

    # 3. 遍历所有配置文件，读配置文件，每一个配置文件是生成一个 SwigConfigFileInfo
    config_dict: dict[str, list[SwigConfigFileInfo]] = {}
    for filename, filepath in swig_filename_to_path.items():
        # 添加 common_swig_config.i
        file_utils.import_swig_config(filepath, common_swig_config_path)
        config = parse_swig_config_file(filename, filepath, java_gen_code_build_dir)
        configs: list[SwigConfigFileInfo] = config_dict.setdefault(config.java_code_outdir, [])
        configs.append(config)

    for java_code_outdir, configs in config_dict.items():
        # 删除上一次生成的文件
        file_utils.remove_dir_and_contents(java_code_outdir)

        class_to_package: dict[str, str] = {}

        for config in configs:
            # 执行 swig 命令
            exec_swig_cmd(config)
            # 校正生成的桥接代码
            adjust_bridge_code(config, config_dict)
            # 替换 swig 生成的 cpp 代码的公共头部
            replace_cpp_bridge_file_common_header(config)
            # 收集类对应的package
            class_to_package.update(config.class_to_package)


        move_build_java_bridge_file(java_code_outdir, class_to_package)




    # 5. 将生成的 java 桥接代码，挪到指定的目录下
    move_java_bridge_file(java_gen_code_build_dir, java_gen_code_src_dir)


def find_swig_config_file(swig_config_dir: str):
    filename_to_path: dict[str, str] = {}

    # 遍历目录及其所有子目录
    for root, dirs, files in os.walk(swig_config_dir):
        for file in files:
            # 检查文件是否以 .i 结尾，且不在配置文件黑名单
            if file.endswith(".i") & (file not in swig_interface_black_list):

                # 获取不带后缀的文件名
                file_name_without_ext = os.path.splitext(file)[0]

                if file_name_without_ext in filename_to_path:
                    raise DuplicateFileNameError(
                        f"重复的文件名: {file_name_without_ext}\n"
                        f"现有路径: {filename_to_path[file_name_without_ext]}\n"
                        f"重复路径: {os.path.join(root, file)}"
                    )

                # 不带后缀的文件名作为键，完整路径作为值
                filename_to_path[file_name_without_ext] = os.path.join(root, file)

    return filename_to_path


# 为指定的配置文件，生成一个 SwigConfigFileInfo
def parse_swig_config_file(filename: str, filepath: str, gen_code_dir: str):
    config = SwigConfigFileInfo()


    config.interface_name = filename

    config.interface_path = filepath
   
    config.cxx_file_path = code_generate_utils.get_wrap_cxx_file(filepath)

    relative_dir = code_generate_utils.get_relative_dir(filepath)

    # project_base/build/...
    outdir = os.path.join(gen_code_dir, relative_dir.lower())
    
    config.java_code_outdir = os.path.abspath(outdir)

    name_to_rename: dict[str, str] = {}
    class_to_package: dict[str, str] = {}
    import_swig_configs: list[str] = []

    config.class_to_package = class_to_package
    config.import_swig_configs = import_swig_configs

    variant_bridge_expression_process_info = ExpressionParseProcessInfo(code_generate_utils.get_variant_bridge_format())

    for line in file_utils.read_file_without_commont(filepath):
        if (config.jniclassName is None) & code_generate_utils.is_module_name_format(line):
            config.jniclassName = code_generate_utils.parse_module_name(line) + "JNI"
        elif (config.jniclasspackage is None) & code_generate_utils.is_jni_package_format(line):
            config.jniclasspackage = code_generate_utils.parse_jni_package(line)
        elif (config.jniclasspackage is None) & code_generate_utils.is_diy_jni_package_format(line):
            config.jniclasspackage = code_generate_utils.parse_diy_jni_package(line)
        elif code_generate_utils.is_rename_format(line):
            key, value = code_generate_utils.parse_rename(line)
            name_to_rename[key] = value
        elif code_generate_utils.is_swig_template_format(line):
            key, value = code_generate_utils.parse_swig_template(line)
            name_to_rename[key] = value
        elif code_generate_utils.is_functional_bridge_format(line):
            key, value = code_generate_utils.parse_functional_bridge(line)
            name_to_rename[key] = value
        elif code_generate_utils.is_java_package_format_2(line):
            key, value = code_generate_utils.parse_java_package_2(line)
            class_to_package[key] = value
        elif code_generate_utils.is_java_package_format(line):
            key, value = code_generate_utils.parse_java_package(line)
            class_to_package[key] = value
        elif code_generate_utils.is_swig_nsp_to_java_format(line):
            key, value = code_generate_utils.parse_swig_nsp_to_java(line)
            config.jniclassName = key + "JNI"
            config.namespace_name = key
            config.jniclasspackage = value
            class_to_package[key] = value
        elif code_generate_utils.is_swig_import_format(line):
            swig_import = code_generate_utils.parse_swig_import(line)
            import_swig_configs.append(swig_import)
        else:
            result = code_generate_utils.parse_swig_expression(variant_bridge_expression_process_info, line)
            if result.match:
                if result.end:
                    key, value = code_generate_utils.parse_variant_bridge(result.full_line)
                    name_to_rename[key] = value
                    variant_bridge_expression_process_info.clear()
                continue

    class_to_package[config.jniclassName] = config.jniclasspackage

    # 处理重命名情况
    for name, rename in name_to_rename.items():
        # 判断 class_to_package 中是否存在 name
        if name in class_to_package:
            class_to_package[rename] = class_to_package[name]

    return config


def remove_dir_and_contents(path):
    try:
        if not os.path.exists(path):
            return
        shutil.rmtree(path)
        print(f"目录 {path} 及其内容已被删除")
    except OSError as e:
        print(f"错误: {path} : {e.strerror}")
        raise e


# 执行 swig 命令，生成原始的桥接代码
def exec_swig_cmd(config: SwigConfigFileInfo):

    source_module_dirs = code_generate_utils.get_source_code_dirs()

    outdir = config.java_code_outdir

    code_generate_utils.run_swig(source_module_dirs, outdir, config.interface_path)



def flatten_config_dict(config_dict: dict[str, list[SwigConfigFileInfo]]) -> list[SwigConfigFileInfo]:
    return [item for sublist in config_dict.values() for item in sublist]


def get_maybe_dependent_classes(self_config: SwigConfigFileInfo, original_config_dict: dict[str, list[SwigConfigFileInfo]]):
    config_dict: dict[str, list[SwigConfigFileInfo]] = {}
    for sublist in original_config_dict.values():
        for config in sublist:
            configs: list[SwigConfigFileInfo] = config_dict.setdefault(config.interface_name, [])
            configs.append(config)


    # 类名 -> 包路径
    result: dict[str, str] = {}
    result.update(self_config.class_to_package)

    for config_file_name in self_config.import_swig_configs:
        if config_file_name in config_dict:
            configs = config_dict[config_file_name]
            for config in configs:
                result.update(config.class_to_package)

    return result




# 校正生成的桥接代码，具体需要校正的的代码如下：
#   需要 director 处理的类，获取 jclass 时，指定的类路径有误，需要替换成正确的类路径
#   swig_new_global_ref(jenv, "XXXBridge") -> swig_new_global_ref(jenv, "jclass_path/XXXBridge")
def adjust_bridge_code(config: SwigConfigFileInfo, config_dict: dict[str, list[SwigConfigFileInfo]]):
    file = config.cxx_file_path
    with open(file, "r", encoding="utf-8") as f1, open("%s.bak" % file, "w", encoding="utf-8") as f2:
        for line in f1:
            if code_generate_utils.is_swig_new_global_ref_format(line):
                class_name = code_generate_utils.parse_swig_new_global_ref(line)
                package_name = config.class_to_package[class_name]
                new_line = code_generate_utils.insert_package(line, package_name)
                f2.write(new_line)
            elif code_generate_utils.is_swig_macro_unfold_comments(line):
                continue
            else:
                f2.write(line)

    # os.remove(file)
    # os.rename("%s.bak" % file, file)
    shutil.move("%s.bak" % file, file)


    # 计算可能依赖的类列表，以及对应的package
    dependent_classes: dict[str, str] = get_maybe_dependent_classes(config, config_dict)

    namespace_class = f"{config.namespace_name}.java" if config.namespace_name is not None else None

    java_class_files = file_utils.get_files_endwith(config.java_code_outdir, [".java"])
    for class_file in java_class_files:
        class_name = file_utils.get_filename_without_extension(class_file)
        package_name = dependent_classes[class_name] if class_name in dependent_classes else None
        dependent_class_names = set(dependent_classes.keys())
        dependent_class_names.discard(class_name)
        imports: set[str] = set()
        with open("%s.bak" % class_file, "w", encoding="utf-8") as f2:
            for line, skip in file_utils.read_file_without_commont_keep_original(class_file):
                if skip:
                     f2.write(line)
                elif line.startswith("pre_package "):
                    if namespace_class is not None and class_file.endswith(namespace_class):
                        new_line = line.replace("pre_package ", "package ")
                        f2.write(new_line)
                elif line.startswith("pre_import "):
                    if namespace_class is not None and class_file.endswith(namespace_class):
                        new_line = line.replace("pre_import ", "import ")
                        f2.write(new_line)        
                else:
                    # 计算下这个类要导哪些包
                    contained_class_names = file_utils.get_contained_classes(line, dependent_class_names)
                    if contained_class_names:
                        dependent_class_names = dependent_class_names - contained_class_names
                        for class_name in contained_class_names:
                            class_package = dependent_classes[class_name]
                            if class_package != package_name:
                                imports.add(f'{dependent_classes[class_name]}.*')
                    f2.write(line)


        code_generate_utils.add_java_imports("%s.bak" % class_file, imports)
        

        shutil.move("%s.bak" % class_file, class_file)
        # os.remove(class_file)
        # os.rename("%s.bak" % class_file, class_file)



# 将生成的 java 桥接代码，根据包路径挪到正确的目录下
def move_build_java_bridge_file(java_code_outdir, class_to_package):

    for root, dirs, files in os.walk(java_code_outdir):
        for file in files:
            filepath = os.path.join(root, file)
            directory, filename = os.path.split(filepath)
            # 分割文件名和扩展名
            filename_without_ext, _ = os.path.splitext(filename)
            if filename_without_ext not in class_to_package:
                file_utils.delete_file(filepath)
                continue
            package_path = class_to_package[filename_without_ext]
            package_path = package_path[len(package_common_pre):].lstrip('.').replace(".", "/")

            finallypath = file_utils.combine_paths(java_gen_code_build_dir, java_code_outdir, package_path)
            file_utils.move_file(filepath, finallypath)

    return


# 替换 swig 生成的 cpp 代码的公共头部
def replace_cpp_bridge_file_common_header(config: SwigConfigFileInfo):

    # 获取生成的 cxx 文件路径
    cxx_file_path = config.cxx_file_path

    # 计算要添加的头文件的相对路径
    common_cpp_headers_relative_path = list(map(lambda path: file_utils.get_relative_path(path, cxx_file_path), common_cpp_headers))

    # 生成 include 表达式
    include_statements = code_generate_utils.generate_include_statements(common_cpp_headers_relative_path)


    replaceInfos: list[ReplaceInfo] = [ReplaceInfo(swig_gen_common_code_line_start, swig_gen_common_code_line_end, include_statements)]

    # 获取要替换的行
    line_num = file_utils.find_target_line_num(cxx_file_path, "template<typename T> class SwigValueWrapper")
    if(line_num != None):
        replaceInfos.append(ReplaceInfo(line_num - 3, line_num + 42, ""))

    # 替换公共头部
    file_utils.replace_lines(cxx_file_path, replaceInfos)

    return


def move_java_bridge_file(src_dir, target_dir):
    # 1. 对比文件夹，计算新增的文件、删除的文件、重复的文件
    new_files, missing_files, duplicate_files = file_utils.compare_dir(src_dir, target_dir, package_common_pre_path)

    # 2. 移动与覆盖文件
    file_utils.cover(src_dir, target_dir, package_common_pre_path)

    # 3. git 处理
    for file in new_files.union(duplicate_files):
        git_utils.git_add(os.path.join(target_dir, file))

    for file in missing_files:
        git_utils.git_rm(os.path.join(target_dir, file))

    cpp_files = file_utils.get_files_target_suffix(cpp_gen_code_dir, [".cxx", ".h"])
    for file in cpp_files:
        git_utils.git_add(file)


# 开始执行
print(f"generate_code start")
generate_code()
print(f"generate_code end")
