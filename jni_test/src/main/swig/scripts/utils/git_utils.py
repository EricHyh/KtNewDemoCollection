import os
import subprocess


def git_add(file_path):
    try:
        subprocess.run(["git", "add", file_path], check=True)
        print(f"Git add: {file_path}")
    except subprocess.CalledProcessError as e:
        print(f"Error executing git add for {file_path}: {e}")




def git_rm(file_path):
    try:
        subprocess.run(["git", "rm", file_path], check=True)
        print(f"Git rm: {file_path}")
    except subprocess.CalledProcessError as e:
        print(f"Error executing git rm for {file_path}: {e}")
