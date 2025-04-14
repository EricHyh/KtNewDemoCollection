import os
import re
import subprocess
from enum import Enum
from contextlib import contextmanager
import file_utils

current_file = os.path.abspath(__file__)
current_dir = os.path.dirname(os.path.abspath(__file__))
scripts_base_dir = os.path.dirname(current_dir)



# java 源码包路径前面的公共部分
package_common_pre = "com.hyh.jnitest"  # 全局搜索，工程配置替换
package_common_pre_path = package_common_pre.replace(".", "/")


# 项目根目录
pro_base_dir = file_utils.get_parent_dir(scripts_base_dir, 4)   # 全局搜索，工程配置替换


# Android 桥接目录
bridge_android_sdk_dir = os.path.join(pro_base_dir, 'src', 'main')  # 全局搜索，工程配置替换


# swig 目录
swig_base_dir = file_utils.get_parent_dir(scripts_base_dir, 1)


# swig 配置文件根目录
swig_config_dir = os.path.join(swig_base_dir, 'cpp')

# swig java代码生成根目录（build）
java_gen_code_build_dir = os.path.join(pro_base_dir, 'build', 'bridge')

# java代码生成根目录
java_gen_code_src_dir = os.path.join(swig_base_dir, 'src')  # 全局搜索，工程配置替换


# cpp代码生成存放目录
cpp_gen_code_dir = os.path.join(swig_base_dir, 'cpp')

# common_swig_config.i 的绝对路径
common_swig_config_path = os.path.join(scripts_base_dir, 'config', 'common_swig_config.i')

# 公共的头文件，在sdk目录下
common_cpp_headers = [  # 全局搜索，工程配置替换
    os.path.join(swig_base_dir, 'cpp', 'swig_gen_common.h'),
    os.path.join(bridge_android_sdk_dir, 'cpp', 'JNIContext.h')
]

# cpp源码目录
cpp_source_code_dir = [ # 全局搜索，工程配置替换
    os.path.join(pro_base_dir, 'src', 'main', 'cpp'),
]


# swig 生成代码公共部分的起始和结束范围
swig_gen_common_code_line_start = 10
swig_gen_common_code_line_end = 783


# cpp代码文件后缀
cpp_gen_code_file_suffix = ["_wrap.cxx", "_wrap.h"]

# 配置黑名单
swig_interface_black_list = []


def is_module_name_format(line):
    return line.strip().startswith("%module")


def parse_module_name(line):
    # 正则表达式模式
    pattern = r"%module\s+(\w+)\s*;?"

    # 使用re.search来查找匹配
    match = re.search(pattern, line)

    if match:
        return match.group(1)
    else:
        return None


# %pragma(java) jniclasspackage=
def is_jni_package_format(line):
    # 正则表达式模式
    pattern = r"^\s*%pragma\s*\(\s*java\s*\)\s+jniclasspackage\s*="

    # 使用re.match来检查是否以指定模式开头
    return bool(re.match(pattern, line.strip()))


def parse_jni_package(line):
    # 正则表达式模式
    pattern = r'%pragma\s*\(\s*java\s*\)\s+jniclasspackage\s*=\s*"([^"]+)"'

    # 使用re.search来查找匹配
    match = re.search(pattern, line)

    # 如果找到匹配，返回捕获的组（包名）
    if match:
        return match.group(1)
    else:
        return None


# %pragma(java) jniclasspackage=
def is_diy_jni_package_format(line):
    return line.strip().startswith('%jni_package_import_')


def parse_diy_jni_package(line):
    # 正则表达式模式
    pattern = r'%jni_package_import_\d+\s*\(\s*([\w.]+)\s*'

    # 使用re.search来查找匹配
    match = re.search(pattern, line)

    # 如果找到匹配，返回捕获的组（包名）
    if match:
        return f"{package_common_pre}.{match.group(1).strip()}"
    else:
        return None



def is_java_package_format(line):
    return line.strip().startswith("%java_package")


def parse_java_package(line):
    # 这个正则表达式匹配两种格式
    pattern = r"%java_package\s*\(\s*(\w+)\s*,\s*([\w.]+)\s*\)"

    match = re.search(pattern, line)
    if match:
        key = match.group(1)
        value = match.group(2)
        if not value.startswith(package_common_pre):
            value = f"{package_common_pre}.{value}"

        return key, value
    else:
        return None, None

def is_java_package_format_2(line):
    return line.strip().startswith("%java_package_import_")


def parse_java_package_2(line):
    # 这个正则表达式匹配两种格式
    pattern = r"%java_package_import_\d+\s*\(\s*([\w:<>]+)\s*,\s*([\w.]+)"

    match = re.search(pattern, line)
    if match:
        key = match.group(1)
        value = match.group(2)
        if not value.startswith(package_common_pre):
            value = f"{package_common_pre}.{value}"

        return key, value
    else:
        return None, None


def is_rename_format(line):
    return line.strip().startswith("%rename")


def parse_rename(line):
    # 正则表达式模式
    pattern = r"%rename\s*\(\s*(\w+)\s*\)\s*(\w+)\s*;?"

    # 使用re.search来查找匹配
    match = re.search(pattern, line.strip())

    # 如果找到匹配，返回一个包含key和value的字典
    if match:
        value = match.group(1)
        key = match.group(2)
        return key, value
    else:
        return None


def is_swig_new_global_ref_format(line):
    # 定义正则表达式模式
    pattern = r'swig_new_global_ref\(jenv,\s*"([^"]+)"\)'

    # 使用re.search来检查字符串中是否包含匹配模式
    return bool(re.search(pattern, line))


def parse_swig_new_global_ref(text):
    # 定义正则表达式模式
    pattern = r'swig_new_global_ref\(jenv,\s*"([^"]+)"\)'

    # 使用正则表达式查找所有匹配
    match = re.search(pattern, text)

    return match.group(1) if match else None

def is_swig_macro_unfold_comments(line):
    pattern = r'/\*@SWIG(?::.*?)?@\*/'
    return bool(re.search(pattern, line))

def is_swig_nsp_to_java_format(line):
    return line.strip().startswith('%nsp_2_java')


def parse_swig_nsp_to_java(line):
    # 定义正则表达式模式
    pattern = r'%nsp_2_java_\d+\s*\(\s*(\w+)\s*,\s*([\w.]+)'

    # 使用正则表达式匹配
    match = re.match(pattern, line)

    if match:
        namespace = match.group(1)
        package = f"{package_common_pre}.{match.group(2).strip()}"
        return namespace.strip(), package.strip()

    return None, None



def is_swig_template_format(line):
    return line.strip().startswith('%template')


def parse_swig_template(line):
    # 定义正则表达式模式
    pattern = r'%template\s*\(\s*(\w+)\s*\)\s*([\w:<>]+)'

    # 使用正则表达式匹配
    match = re.match(pattern, line)

    if match:
        target_type = match.group(1)
        original_type = match.group(2)
        return original_type.strip(), target_type.strip()

    return None, None


def is_swig_import_format(line):
    return line.strip().startswith('%import')

def parse_swig_import(line):
    # 更新的正则表达式模式
    pattern = r'%import\s+"?([^"\s]+)"?\s*;?'

    # 使用re.search来查找匹配
    match = re.search(pattern, line)

    if match:
        full_path = match.group(1)
        # 提取文件名
        filename = full_path.split('/')[-1]
        # 如果文件名以 .i 结尾，去掉 .i
        if filename.endswith('.i'):
            filename = filename[:-2]
        return filename
    else:
        return None
    

def is_functional_bridge_format(line):
    return line.strip().startswith('%functional_bridge')

def parse_functional_bridge(line):
    pattern = r'%functional_bridge\s*\(\s*([^,]+?)\s*,\s*([^,]+?)\s*,'
    match = re.search(pattern, line)
    
    if match:
        return match.group(1).strip(), match.group(2).strip()
    else:
        return None, None
    

def get_variant_bridge_format():
    # 合并的正则表达式模式
    return r'^%variant_(with_empty_)?bridge_\d+'
    
def parse_variant_bridge(line)-> tuple[str, str]:
    pattern = r'%(variant_(?:with_empty_)?bridge_\d+)\s*\(\s*(\w+)\s*,\s*(\w+)'
    match = re.match(pattern, line)
    if match:
        return match.group(2), match.group(3)
    return '', ''

def insert_package(line: str, package_path: str):
    # 定义正则表达式模式

    package_path = package_path.replace(".", "/")
    pattern = r'(swig_new_global_ref\(jenv,\s*")([^"]+)(")'

    # 定义替换函数
    def replace_func(match):
        return f"{match.group(1)}{package_path}/{match.group(2)}{match.group(3)}"

    # 使用re.sub进行替换
    result = re.sub(pattern, replace_func, line)

    return result


def get_relative_dir(abs_path: str):

    # 标准化路径，处理不同操作系统的路径分隔符
    full_path = os.path.normpath(abs_path)
    base_path = os.path.normpath(cpp_gen_code_dir)

    
    # 检查基础路径是否在完整路径中
    if base_path not in full_path:
        raise ValueError(f"Base path '{base_path}' not found in '{full_path}'")
    
    # 提取基础路径之后的部分
    relative_path = os.path.relpath(full_path, base_path)
    
    # 移除文件名
    directory_path = os.path.dirname(relative_path)
    
    return directory_path


def get_wrap_cxx_file(interface_file, check_exists=False):
    directory, filename = os.path.split(interface_file)

    if not filename.endswith(".i"):
        raise ValueError(f"The file {filename} is not a .i file")

    base_name = os.path.splitext(filename)[0]
    wrap_cxx_filename = f"{base_name}_wrap.cxx"
    wrap_cxx_file_path = os.path.join(directory, wrap_cxx_filename)

    if check_exists and not os.path.exists(wrap_cxx_file_path):
        raise FileNotFoundError(f"The file {wrap_cxx_filename} does not exist in the directory")

    return wrap_cxx_file_path


def get_source_code_dirs():
    swig_config_dirs = file_utils.get_first_level_subdirectories(swig_config_dir)
    unique_dirs = set(cpp_source_code_dir) | set(swig_config_dirs)
    return list(unique_dirs)


def generate_include_statements(header_paths):
    return '\n'.join(f'#include "{path}"' for path in header_paths)


def add_java_imports(class_file_path, imports):
        # 读取文件内容
    with open(class_file_path, 'r', encoding="utf-8") as file:
        content = file.read()

    # 查找包声明的位置
    package_match = re.search(r'^package\s+[\w.]+;', content, re.MULTILINE)
    
    if package_match:
        insert_position = package_match.end()
    else:
        # 如果没有包声明，就在文件开头插入
        insert_position = 0

    # 准备新的导入语句
    new_imports = '\n'.join(f"import {imp};" for imp in imports)
    
    # 如果已经有导入语句，在它们之后添加新的导入
    existing_imports = re.search(r'(import\s+[\w.]+;\n)+', content[insert_position:])
    if existing_imports:
        insert_position += existing_imports.end()
        new_imports = '\n' + new_imports

    # 插入新的导入语句
    new_content = content[:insert_position] + '\n' + new_imports + '\n' + content[insert_position:]

    # 写回文件
    with open(class_file_path, 'w', encoding="utf-8") as file:
        file.write(new_content)


class ExpressionParseProcessInfo:
    def __init__(self, pattern: str):
        self.pattern: str = pattern
        self.collected_lines: list[str] = []
        self.in_process: bool = False
        self.bracket_count: int = 0
    
    def clear(self):
        self.collected_lines = []
        self.in_process = False
        self.bracket_count = 0

class ExpressionParseResult:
    def __init__(self):
        self.match: bool = False
        self.end: bool = False
        self.full_line: str = None


def parse_swig_expression(info: ExpressionParseProcessInfo, line: str) -> ExpressionParseResult:
    result: ExpressionParseResult = ExpressionParseResult()
    line = line.strip()

    if not info.in_process:
        if re.match(info.pattern, line):
            result.match = True
            result.end = False
            info.in_process = True
            info.collected_lines = [line]
    elif info.in_process:
        result.match = True
        result.end = False
        info.collected_lines.append(line)


    if info.in_process:
        if info.bracket_count > 0:
            info.bracket_count += line.count('(') - line.count(')')
            if info.bracket_count == 0:
                result.end = True
        elif info.bracket_count == 0:
            info.bracket_count += line.count('(') - line.count(')')
            if info.bracket_count == 0 and '(' in line:
                result.end = True
              
    
    if result.end:
        collected_lines = info.collected_lines
        if collected_lines:
            # 合并行并移除多余的空白字符
            full_declaration = ' '.join(collected_lines)
            # 使用正则表达式替换多个空白字符为单个空格，但保留括号内的空格
            full_declaration = re.sub(r'\s+(?=[^()]*\))', ' ', full_declaration)
            # 确保函数名和左括号之间没有空格
            full_declaration = re.sub(r'(\w+)\s*\(', r'\1(', full_declaration)
            result.full_line = full_declaration.strip()

    return result



@contextmanager
def change_directory(path):
    origin = os.getcwd()
    try:
        os.chdir(path)
        yield
    finally:
        os.chdir(origin)


def run_swig(source_module_dirs, outdir, interface_file):

    # 确保输出目录存在
    os.makedirs(outdir, exist_ok=True)

    swig_cmd = ["swig", "-c++", "-java"]
    # 添加所有源模块目录作为 include 路径
    for source_dir in source_module_dirs:
        swig_cmd.append(f"-I{source_dir}")

    swig_cmd.extend(["-outdir", outdir, "-directors", interface_file])

    # swig_cmd = ["swig", "-c++", "-java", f"-I{source_module_dirs}", "-outdir", outdir, "-directors", interface_file]

    try:
        result = subprocess.run(swig_cmd, check=True, capture_output=True, text=True)
        print("SWIG 命令执行成功")
        print("输出:", result.stdout)
    except subprocess.CalledProcessError as e:
        print("SWIG 命令执行失败")
        print("错误输出:", e.stderr)
        raise
