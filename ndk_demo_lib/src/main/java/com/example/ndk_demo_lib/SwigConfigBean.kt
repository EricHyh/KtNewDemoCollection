package com.example.ndk_demo_lib


/**
 * TODO: Add Description
 *
 * @author eriche 2024/12/17
 */


object Flag {

    const val shared_ptr = 0

    const val optional = 0


}

data class ModuleConfig(
    val module_name: String,
    val path_dir: String,
    val type_configs: List<TypeConfig>,
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

    val dependent_types: List<String>,
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

    val dependent_types: List<String>
)

data class FunctionConfig(
    val source_path: String,
    val original_type: String,
    val target_type: String,
    val is_template: Boolean,

    //val template_name: String,
    val params: Pair<String, String>,

    val dependent_types: List<String>
)

data class VariantConfig(
    val source_path: String,
    val original_type: String,
    val target_type: String,
    val is_template: Boolean,

    val variant_types: Pair<String, String>,
    val dependent_types: List<String>
)


data class CollectionConfig(
    val source_path: String,
    val original_type: String,
    val target_type: String,

    val dependent_types: List<String>
)


data class TemplateConfig(
    val source_path: String,
    val original_type: String,
    val target_type: String,

    val dependent_types: List<String>
)


/**
 * %variant_bridge_5(TestVariant, TestVariantBridge,
 *                     int, Int,
 *                     double, Double,
 *                     std::string, String,
 *                     bool, Bool,
 *                     int64_t, Long);
 *
 * %java_package(std::variant<int __COMMA__ double __COMMA__ std::string __COMMA__ bool __COMMA__ int64_t>, com.example.ndk_demo_lib2)
 *
 * %shared_type_bridge(std::variant<int __COMMA__ double __COMMA__ std::string __COMMA__ bool __COMMA__ int64_t>, TestVariantBridge, TestVariantBridge)
 *
 */