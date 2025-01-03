package com.example.ndk_demo_lib


/**
 * TODO: Add Description
 *
 * @author eriche 2024/12/17
 */


data class ModuleConfig(
    val module_name: String,
    val path_dir: String,
    val classes: List<ClassConfig>,
)

data class TypeConfig(
    val type: Int,
    val class_config: ClassConfig?,
    val enumclass_config: EnumClassConfig?,
    val namespace_config: NamespaceConfig?,
    val function_config: FunctionConfig?,
)


// ClassConfig -> BuildInfo()
// source_path -> List<ClassConfig>

data class ClassConfig(
    val source_path: String,
    val original_type: String,
    val target_type: String,
    val is_template: Boolean,
    val shared_ptr: Boolean,
    val detector: Boolean,

    val dependent_modules: List<String>,
)

data class EnumClassConfig(
    val source_path: String,
    val original_type: String,
    val target_type: String,
)

data class NamespaceConfig(
    val source_path: String,
    val original_type: String,
    val target_type: String,

    val dependent_modules: List<String>
)

data class FunctionConfig(
    val source_path: String,
    val original_type: String,
    val target_type: String,
    val is_template: Boolean,

    //val template_name: String,
    val params: Pair<String, String>,

    val dependent_modules: List<String>
)