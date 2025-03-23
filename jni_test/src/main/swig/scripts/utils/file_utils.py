import os
import re
import time
import shutil
import filecmp

def get_first_level_subdirectories(swig_config_dir):
    # 确保路径存在
    if not os.path.exists(swig_config_dir):
        raise FileNotFoundError(f"Directory not found: {swig_config_dir}")

    # 确保路径是一个目录
    if not os.path.isdir(swig_config_dir):
        raise NotADirectoryError(f"Not a directory: {swig_config_dir}")

    # 获取所有第一级子目录
    subdirectories = [
        os.path.join(swig_config_dir, d) for d in os.listdir(swig_config_dir)
        if os.path.isdir(os.path.join(swig_config_dir, d))
    ]

    return subdirectories

def get_parent_dir(current, levels = 1):
    current = current
    for _ in range(levels):
        current = os.path.dirname(current)
    return current

def get_filename_without_extension(file):
    # 获取文件名（可能包含扩展名）
    filename = os.path.basename(file)
    
    # 分离文件名和扩展名
    name, ext = os.path.splitext(filename)
    
    # 返回没有扩展名的文件名
    return name


def combine_paths(base_dir, mid_dir, package_path):
    # 标准化所有路径
    base_dir = os.path.normpath(base_dir)
    mid_dir = os.path.normpath(mid_dir)
    package_path = os.path.normpath(package_path)

    # 确保 mid_dir 是 base_dir 的子目录
    if not mid_dir.startswith(base_dir):
        raise ValueError(f"mid_dir '{mid_dir}' is not a subdirectory of base_dir '{base_dir}'")

    # 从 mid_dir 中提取 base_dir 之后的部分
    mid_suffix = os.path.relpath(mid_dir, base_dir)

    # 分割 package_path
    package_parts = package_path.split(os.sep)

    # 找到 mid_suffix 和 package_path 的重叠部分
    overlap = 0
    mid_parts = mid_suffix.split(os.sep)
    for i in range(min(len(mid_parts), len(package_parts))):
        if mid_parts[i] != package_parts[i]:
            break
        overlap += 1

    # 组合最终路径
    result_path = os.path.join(mid_dir, *package_parts[overlap:])

    return result_path

# def combine_paths(base_dir, mid_dir, package_path):
#     # 规范化路径
#     base_path = os.path.normpath(base_path)
#     package_path = os.path.normpath(package_path)

#     # 定义 swig_dir
#     swig_dir = os.path.join('bridge', 'Android', 'sdk', 'build', 'generated', 'swig')
#     swig_dir = os.path.join('bridge', 'Android', 'sdk', 'build', 'generated', 'swig')

#     # 找到 swig_dir 在 base_path 中的位置
#     swig_index = base_path.find(swig_dir)

#     if swig_index == -1:
#         raise ValueError("base_path does not contain the expected 'bridge/Android/sdk/swig' directory")

#     # 提取 "swig" 之后的组件
#     suffix_start = swig_index + len(swig_dir)
#     base_suffix = base_path[suffix_start:].lstrip(os.sep)

#     # 将 base_suffix 和 package_path 分割成组件
#     base_suffix_components = base_suffix.split(os.sep)
#     package_components = package_path.split(os.sep)

#     # 找到重合部分的长度
#     overlap_length = 0
#     for i in range(min(len(base_suffix_components), len(package_components))):
#         if base_suffix_components[i] == package_components[i]:
#             overlap_length = i + 1
#         else:
#             break

#     # 去除 package_path 中的重合部分
#     unique_package_components = package_components[overlap_length:]

#     # 组合路径
#     combined_path = os.path.join(base_path, *unique_package_components)

#     return combined_path


def path_contains_directory(path, directory):
    # 将路径规范化，以处理不同的路径格式
    norm_path = os.path.normpath(path)
    norm_directory = os.path.normpath(directory)

    # 检查规范化后的目录是否是路径的一部分
    return norm_directory in norm_path


def delete_file(file_path):
    """
    删除指定路径的文件。

    :param file_path: 要删除的文件的路径
    :return: 如果删除成功返回 True，否则返回 False
    """
    try:
        # 检查文件是否存在
        if not os.path.exists(file_path):
            print(f"错误：文件不存在 - {file_path}")
            return False

        # 检查是否为文件（而不是目录）
        if not os.path.isfile(file_path):
            print(f"错误：指定路径不是文件 - {file_path}")
            return False

        # 删除文件
        os.remove(file_path)
        # 或者使用 os.unlink(file_path)

        print(f"文件已成功删除：{file_path}")
        return True

    except PermissionError:
        print(f"错误：没有权限删除文件 - {file_path}")
    except OSError as e:
        print(f"删除文件时发生错误：{e}")
    except Exception as e:
        print(f"发生未知错误：{e}")

    return False


def remove_dir_and_contents(path):
    try:
        if not os.path.exists(path):
            return
        shutil.rmtree(path)
        print(f"目录 {path} 及其内容已被删除")
    except OSError as e:
        print(f"错误: {path} : {e.strerror}")
        raise e


def compare_dir(src_dir, target_dir, target_dir_pre_path):
    # 获取源目录中的所有文件并添加前缀
    
    src_files = {os.path.join(target_dir_pre_path, f) if target_dir_pre_path else f for f in get_subfile_relative_path(src_dir)}

    # 获取目标目录中的所有文件
    target_files = set(get_subfile_relative_path(target_dir))

    # 1. 计算新增的文件
    new_files = src_files - target_files

    # 2. 计算没有的文件
    missing_files = target_files - src_files

    # 3. 计算重复的文件（在src_dir和target_dir中都存在的文件）
    duplicate_files = src_files.intersection(target_files)

    return new_files, missing_files, duplicate_files


def get_subfile_relative_path(directory):
    file_list = []
    for root, _, files in os.walk(directory):
        for file in files:
            # 获取相对路径
            relative_path = os.path.relpath(os.path.join(root, file), directory)
            file_list.append(relative_path)
    return file_list


def convert_paths(file_set, from_dir, to_dir):
    converted = set()
    for file in file_set:
        # 构建完整路径
        full_path = os.path.join(from_dir, file)
        # 转换为相对于 to_dir 的路径
        relative_path = os.path.relpath(full_path, to_dir)
        converted.add(relative_path)
    return converted


def cover(src_dir, target_dir, target_dir_pre_path):
    # 确保源目录存在
    if not os.path.exists(src_dir):
        raise FileNotFoundError(f"Source directory '{src_dir}' does not exist.")

    # 如果目标目录不存在，创建它
    if not os.path.exists(target_dir):
        os.makedirs(target_dir)

    # 创建带前缀的目标目录
    prefixed_target_dir = os.path.join(target_dir, target_dir_pre_path)
    if not os.path.exists(prefixed_target_dir):
        os.makedirs(prefixed_target_dir)

    # 删除带前缀的目标目录中的所有内容
    for item in os.listdir(prefixed_target_dir):
        item_path = os.path.join(prefixed_target_dir, item)
        if os.path.isfile(item_path) or os.path.islink(item_path):
            os.unlink(item_path)
        elif os.path.isdir(item_path):
            shutil.rmtree(item_path)

    # 复制源目录的内容到带前缀的目标目录
    for item in os.listdir(src_dir):
        s = os.path.join(src_dir, item)
        d = os.path.join(prefixed_target_dir, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks=True)
        else:
            shutil.copy2(s, d)

    print(f"Successfully covered '{prefixed_target_dir}' with contents from '{src_dir}'.")


def move_file(source_path, destination_directory):
    """
    将文件从源路径移动到目标目录。

    :param source_path: 源文件的完整路径
    :param destination_directory: 目标目录的路径
    :return: 如果移动成功返回 True，否则返回 False
    """
    try:
        # 检查源文件是否存在
        if not os.path.exists(source_path):
            print(f"错误：源文件不存在 - {source_path}")
            return False

        # 检查源路径是否为文件
        if not os.path.isfile(source_path):
            print(f"错误：源路径不是一个文件 - {source_path}")
            return False

        # 确保目标目录存在，如果不存在则创建
        os.makedirs(destination_directory, exist_ok=True)

        # 获取文件名
        file_name = os.path.basename(source_path)

        # 构建目标文件的完整路径
        destination_path = os.path.join(destination_directory, file_name)

        # 检查目标路径是否已存在文件
        if os.path.exists(destination_path):
            print(f"警告：目标路径已存在同名文件 - {destination_path}")

        # 移动文件
        shutil.move(source_path, destination_path)
        source_directory, _ = os.path.split(source_path)
        remove_empty_dirs_up_to_sdk(source_directory)
        print(f"文件已成功移动到 {destination_path}")
        return True

    except PermissionError:
        print(f"错误：没有足够的权限来移动文件 - {source_path}")
    except shutil.Error as e:
        print(f"移动文件时发生错误：{e}")
    except Exception as e:
        print(f"发生未知错误：{e}")

    return False


def remove_empty_dirs_up_to_sdk(start_path, end_dir=["swig", "build"]):
    """
    删除空目录，并向上删除空的父目录，直到遇到非空目录或名为'sdk'的目录

    :param start_path: 开始删除的目录路径
    :return: 最后删除的目录路径（如果有的话）
    """
    if not os.path.isdir(start_path):
        print(f"The path is not a directory: {start_path}")
        return None

    last_removed = None
    current_path = os.path.abspath(start_path)

    while True:
        if os.path.basename(current_path) in end_dir:
            print(f"Reached 'sdk' directory: {current_path}")
            break

        try:
            # 检查目录是否为空
            if os.listdir(current_path):
                print(f"Directory is not empty: {current_path}")
                break

            # 删除当前空目录
            os.rmdir(current_path)
            print(f"Removed empty directory: {current_path}")
            last_removed = current_path

            # 移动到父目录
            current_path = os.path.dirname(current_path)
        except OSError as e:
            print(f"Error processing directory {current_path}: {e}")
            break

    return last_removed


def get_files_target_suffix(dir, suffix):
    """
    获取指定目录下所有以给定后缀结尾的文件

    :param dir: 要搜索的目录路径
    :param suffix: 文件后缀列表
    :return: 符合条件的文件路径列表
    """
    matching_files = []

    # 确保所有后缀都以 '.' 开头
    suffix = [s if s.startswith(".") else "." + s for s in suffix]

    # 遍历目录
    for root, dirs, files in os.walk(dir):
        for file in files:
            # 检查文件是否以任何一个给定的后缀结尾
            if any(file.endswith(s) for s in suffix):
                # 将符合条件的文件的完整路径添加到列表中
                matching_files.append(os.path.join(root, file))

    return matching_files


def get_files_endwith(dir, endwith):
    """
    获取指定目录下所有以给定后缀结尾的文件

    :param dir: 要搜索的目录路径
    :param suffix: 文件后缀列表
    :return: 符合条件的文件路径列表
    """
    matching_files = []

    # 遍历目录
    for root, dirs, files in os.walk(dir):
        for file in files:
            # 检查文件是否以任何一个给定的后缀结尾
            if any(file.endswith(s) for s in endwith):
                # 将符合条件的文件的完整路径添加到列表中
                matching_files.append(os.path.join(root, file))

    return matching_files

def get_relative_path(file_path, target_file_path):
    # 获取 targetFilePath 的目录
    target_dir = os.path.dirname(target_file_path)

    # 确保路径是绝对路径
    file_path = os.path.abspath(file_path)
    target_dir = os.path.abspath(target_dir)

    # 计算相对路径
    rel_path = os.path.relpath(file_path, target_dir)

    # 使用正斜杠替换反斜杠
    rel_path = rel_path.replace(os.sep, '/')

    return rel_path


class ReplaceInfo:
    start_line : int

    end_line: int

    replacement_text: str

    def __init__(self, start_line: int, end_line: int, replacement_text: str):
        self.start_line = start_line
        self.end_line = end_line
        self.replacement_text = replacement_text


# def replace_lines(file_path, start_line, end_line, replacement_text):
#     # 读取原文件内容
#     with open(file_path, 'r', encoding='utf-8') as file:
#         lines = file.readlines()

#     print(f"")

#     # 替换指定范围的行
#     lines[start_line-1:end_line] = [replacement_text + '\n']

#     print(f"")

#     # 写回文件
#     with open(file_path, 'w', encoding='utf-8') as file:
#         file.writelines(lines)


def replace_lines(file_path: str, replaceInfos: list[ReplaceInfo]):
    # 读取文件的所有行
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()

    # 按照起始行从大到小排序 replaceInfos，以避免earlier替换影响later的行号
    replaceInfos.sort(key=lambda x: x.start_line, reverse=True)

    # 对每个 ReplaceInfo 进行处理
    for info in replaceInfos:
        # 确保起始行和结束行有效
        if 1 <= info.start_line <= len(lines) and 1 <= info.end_line <= len(lines):
            # 将 replacement_text 分割成行
            new_lines = info.replacement_text.splitlines(keepends=True)
            # 如果 new_lines 为空列表，添加一个只包含换行符的元素
            if not new_lines:
                new_lines = ['\n']
            # 如果最后一行不以换行符结束，添加换行符
            elif not new_lines[-1].endswith('\n'):
                new_lines[-1] += '\n'

            # 替换指定范围的行
            lines[info.start_line-1:info.end_line] = new_lines

    # 将修改后的内容写回文件
    with open(file_path, 'w', encoding='utf-8') as file:
        file.writelines(lines)


def find_target_line_num(file_path, target_line):
    with open(file_path, 'r', encoding='utf-8') as file:
        for line_number, line in enumerate(file, 1):
            if line.strip().startswith(target_line):
                return line_number

    return None  # 如果没有找到匹配的行



def import_swig_config(original_config_file, import_config_relative_path):

    # 获取原始配置文件的目录
    original_config_dir = os.path.dirname(original_config_file)

    # 将相对路径与原始配置文件目录结合
    full_import_path = os.path.join(original_config_dir, import_config_relative_path)

    # 标准化路径（解析 '..' 和 '.'）
    normalized_import_path = os.path.normpath(full_import_path)

    # 计算相对于原始配置文件目录的相对路径
    relative_import_path = os.path.relpath(normalized_import_path, original_config_dir)

    # 将路径分割成各个部分
    path_parts = relative_import_path.split(os.sep)

    relative_import_path = '/'.join(path_parts)

    # 构造新的导入语句
    new_import_line = f'%include "{relative_import_path}"'

    # 读取原始配置文件的内容
    with open(original_config_file, 'r', encoding='utf-8') as file:
        lines = file.readlines()

    import_pattern = r'^%(include|import)\s*".*common_swig_config\.i"'
    if lines and re.match(import_pattern, lines[0].strip()):
        # 如果匹配，替换第一行
        lines[0] = new_import_line + '\n'
    else:
        # 如果不匹配，在开头插入新行
        lines.insert(0, new_import_line + '\n')

    # 将更新后的内容写回文件
    with open(original_config_file, 'w', encoding='utf-8') as file:
        file.writelines(lines)

# 阅读文件，跳过空行和注释
def read_file_without_commont(file_path):
    in_multiline_comment = False
    with open(file_path, 'r', encoding="utf-8") as file:
        for line in file:
            line = line.strip()
            if not line:
                continue

            if in_multiline_comment:
                if '*/' in line:
                    in_multiline_comment = False
                    line = line.split('*/', 1)[-1]
                else:
                    continue

            if '//' in line:
                line = line.split('//', 1)[0]

            if '/*' in line:
                if '*/' in line:
                    line = line.split('/*', 1)[0] + line.split('*/', 1)[-1]
                else:
                    in_multiline_comment = True
                    line = line.split('/*', 1)[0]

            if line:
                yield line


# 阅读文件，跳过空行和注释，但是保留原始行信息
def read_file_without_commont_keep_original(file_path):
    in_multiline_comment = False
    with open(file_path, 'r', encoding="utf-8") as file:
        for line in file:
            original_line = line
            line = line.strip()

            # 处理空行
            if not line:
                yield (original_line, True)
                continue

            # 处理多行注释
            if in_multiline_comment:
                if '*/' in line:
                    in_multiline_comment = False
                    line = line.split('*/', 1)[-1].strip()
                else:
                    yield (original_line, True)
                    continue

            # 处理单行注释
            if line.startswith('//'):
                yield (original_line, True)
                continue

            # 处理多行注释的开始
            if '/*' in line:
                if '*/' in line:
                    # 单行内的多行注释
                    line = line.split('/*', 1)[0] + line.split('*/', 1)[-1]
                else:
                    in_multiline_comment = True
                    line = line.split('/*', 1)[0]
                    if not line:
                        yield (original_line, True)
                        continue

            # 移除行内注释
            if '//' in line:
                line = line.split('//', 1)[0].strip()

            if line:
                yield (original_line, False)
            else:
                yield (original_line, True)



def get_contained_classes(line: str, classes: list[str]) -> set[str]:
    
    # 将类名列表转换为正则表达式模式
    class_pattern = r'(?<![.\w])(' + '|'.join(re.escape(cls) for cls in classes) + r')(?=[^\w]|\s*$)'

    # 使用集合来去重，同时用列表保持顺序
    contained_classes = set()
    
    # 使用re.finditer查找所有匹配的类名
    for match in re.finditer(class_pattern, line):
        cls = match.group(1)
        if cls not in contained_classes:
            contained_classes.add(cls)
    
    return contained_classes