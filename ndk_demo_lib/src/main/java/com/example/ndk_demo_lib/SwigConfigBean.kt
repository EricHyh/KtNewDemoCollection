package com.example.ndk_demo_lib

/**
 * TODO: Add Description
 *
 * @author eriche 2024/12/17
 */




data class ModuleConfig(
    val module_name: String,
    val package_name: String,
    val imports: List<String>,
)

data class ClassConfig(
    val original_name: String,
    val rename: String,
    val package_name: String,
    val imports: List<String>,
)

data class FunctionConfig(
    val original_name: String,
    val rename: String,
    val package_name: String,
    val imports: List<String>,

    val template_name: String,
    val params: List<String>,
)


data class NameSpaceConfig(
    val original_name: String,
    val rename: String,
    val package_name: String,
    val imports: List<String>,
)