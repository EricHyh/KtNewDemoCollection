/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


#include "../../swig_gen_common.h"
#include "../../../../cpp/JNIContext.h"





#include <map>
#include <unordered_map>
#include <variant>
#include <memory>
#include <mutex>
#include <list>
#include <vector>
#include <functional>


/* Check for overflow converting to Java int (always signed 32-bit) from (unsigned variable-bit) size_t */
SWIGINTERN jint SWIG_JavaIntFromSize_t(size_t size) {
  static const jint JINT_MAX = 0x7FFFFFFF;
  return (size > (size_t)JINT_MAX) ? -1 : (jint)size;
}


SWIGINTERN jint SWIG_VectorSize(size_t size) {
  jint sz = SWIG_JavaIntFromSize_t(size);
  if (sz == -1)
    throw std::out_of_range("vector size is too large to fit into a Java int");
  return sz;
}

SWIGINTERN std::vector< std::string > *new_std_vector_Sl_std_string_Sg___SWIG_2(jint count,std::string const &value){
        if (count < 0)
          throw std::out_of_range("vector count must be positive");
        return new std::vector< std::string >(static_cast<std::vector< std::string >::size_type>(count), value);
      }
SWIGINTERN jint std_vector_Sl_std_string_Sg__doCapacity(std::vector< std::string > *self){
        return SWIG_VectorSize(self->capacity());
      }
SWIGINTERN void std_vector_Sl_std_string_Sg__doReserve(std::vector< std::string > *self,jint n){
        if (n < 0)
          throw std::out_of_range("vector reserve size must be positive");
        self->reserve(n);
      }
SWIGINTERN jint std_vector_Sl_std_string_Sg__doSize(std::vector< std::string > const *self){
        return SWIG_VectorSize(self->size());
      }
SWIGINTERN void std_vector_Sl_std_string_Sg__doAdd__SWIG_0(std::vector< std::string > *self,std::vector< std::string >::value_type const &x){
        self->push_back(x);
      }
SWIGINTERN void std_vector_Sl_std_string_Sg__doAdd__SWIG_1(std::vector< std::string > *self,jint index,std::vector< std::string >::value_type const &x){
        jint size = static_cast<jint>(self->size());
        if (0 <= index && index <= size) {
          self->insert(self->begin() + index, x);
        } else {
          throw std::out_of_range("vector index out of range");
        }
      }
SWIGINTERN std::vector< std::string >::value_type std_vector_Sl_std_string_Sg__doRemove(std::vector< std::string > *self,jint index){
        jint size = static_cast<jint>(self->size());
        if (0 <= index && index < size) {
          std::string const old_value = (*self)[index];
          self->erase(self->begin() + index);
          return old_value;
        } else {
          throw std::out_of_range("vector index out of range");
        }
      }
SWIGINTERN std::vector< std::string >::value_type const &std_vector_Sl_std_string_Sg__doGet(std::vector< std::string > *self,jint index){
        jint size = static_cast<jint>(self->size());
        if (index >= 0 && index < size)
          return (*self)[index];
        else
          throw std::out_of_range("vector index out of range");
      }
SWIGINTERN std::vector< std::string >::value_type std_vector_Sl_std_string_Sg__doSet(std::vector< std::string > *self,jint index,std::vector< std::string >::value_type const &val){
        jint size = static_cast<jint>(self->size());
        if (index >= 0 && index < size) {
          std::string const old_value = (*self)[index];
          (*self)[index] = val;
          return old_value;
        }
        else
          throw std::out_of_range("vector index out of range");
      }
SWIGINTERN void std_vector_Sl_std_string_Sg__doRemoveRange(std::vector< std::string > *self,jint fromIndex,jint toIndex){
        jint size = static_cast<jint>(self->size());
        if (0 <= fromIndex && fromIndex <= toIndex && toIndex <= size) {
          self->erase(self->begin() + fromIndex, self->begin() + toIndex);
        } else {
          throw std::out_of_range("vector index out of range");
        }
      }


/* ---------------------------------------------------
 * C++ director class methods
 * --------------------------------------------------- */

#include "infrastructure_wrap.h"


#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT jlong JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_new_1StringVector_1_1SWIG_10(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  std::vector< std::string > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (std::vector< std::string > *)new std::vector< std::string >();
  *(std::vector< std::string > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_new_1StringVector_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  std::vector< std::string > *arg1 = 0 ;
  std::vector< std::string > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1;
  if (!arg1) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "std::vector< std::string > const & is null");
    return 0;
  } 
  result = (std::vector< std::string > *)new std::vector< std::string >((std::vector< std::string > const &)*arg1);
  *(std::vector< std::string > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jboolean JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1isEmpty(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jboolean jresult = 0 ;
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  bool result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  result = (bool)((std::vector< std::string > const *)arg1)->empty();
  jresult = (jboolean)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1clear(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  (arg1)->clear();
}


SWIGEXPORT jlong JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_new_1StringVector_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jint jarg1, jstring jarg2) {
  jlong jresult = 0 ;
  jint arg1 ;
  std::string *arg2 = 0 ;
  std::vector< std::string > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = jarg1; 
  if(!jarg2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
    return 0;
  }
  const char *arg2_pstr = (const char *)jenv->GetStringUTFChars(jarg2, 0); 
  if (!arg2_pstr) return 0;
  std::string arg2_str(arg2_pstr);
  arg2 = &arg2_str;
  jenv->ReleaseStringUTFChars(jarg2, arg2_pstr); 
  try {
    result = (std::vector< std::string > *)new_std_vector_Sl_std_string_Sg___SWIG_2(SWIG_STD_MOVE(arg1),(std::string const &)*arg2);
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return 0;
  }
  *(std::vector< std::string > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doCapacity(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  jint result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  try {
    result = std_vector_Sl_std_string_Sg__doCapacity(arg1);
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return 0;
  }
  jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doReserve(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  jint arg2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  arg2 = jarg2; 
  try {
    std_vector_Sl_std_string_Sg__doReserve(arg1,SWIG_STD_MOVE(arg2));
  } catch(std::length_error &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return ;
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return ;
  }
}


SWIGEXPORT jint JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doSize(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  jint result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  try {
    result = std_vector_Sl_std_string_Sg__doSize((std::vector< std::string > const *)arg1);
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return 0;
  }
  jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doAdd_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2) {
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  std::vector< std::string >::value_type *arg2 = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  if(!jarg2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
    return ;
  }
  const char *arg2_pstr = (const char *)jenv->GetStringUTFChars(jarg2, 0); 
  if (!arg2_pstr) return ;
  std::vector< std::string >::value_type arg2_str(arg2_pstr);
  arg2 = &arg2_str;
  jenv->ReleaseStringUTFChars(jarg2, arg2_pstr); 
  std_vector_Sl_std_string_Sg__doAdd__SWIG_0(arg1,(std::string const &)*arg2);
}


SWIGEXPORT void JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doAdd_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jstring jarg3) {
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  jint arg2 ;
  std::vector< std::string >::value_type *arg3 = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  arg2 = jarg2; 
  if(!jarg3) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
    return ;
  }
  const char *arg3_pstr = (const char *)jenv->GetStringUTFChars(jarg3, 0); 
  if (!arg3_pstr) return ;
  std::vector< std::string >::value_type arg3_str(arg3_pstr);
  arg3 = &arg3_str;
  jenv->ReleaseStringUTFChars(jarg3, arg3_pstr); 
  try {
    std_vector_Sl_std_string_Sg__doAdd__SWIG_1(arg1,SWIG_STD_MOVE(arg2),(std::string const &)*arg3);
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return ;
  }
}


SWIGEXPORT jstring JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doRemove(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jstring jresult = 0 ;
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  jint arg2 ;
  std::vector< std::string >::value_type result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  arg2 = jarg2; 
  try {
    result = std_vector_Sl_std_string_Sg__doRemove(arg1,SWIG_STD_MOVE(arg2));
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return 0;
  }
  jresult = jenv->NewStringUTF((&result)->c_str()); 
  return jresult;
}


SWIGEXPORT jstring JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doGet(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jstring jresult = 0 ;
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  jint arg2 ;
  std::vector< std::string >::value_type *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  arg2 = jarg2; 
  try {
    result = (std::vector< std::string >::value_type *) &std_vector_Sl_std_string_Sg__doGet(arg1,SWIG_STD_MOVE(arg2));
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return 0;
  }
  jresult = jenv->NewStringUTF(result->c_str()); 
  return jresult;
}


SWIGEXPORT jstring JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doSet(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jstring jarg3) {
  jstring jresult = 0 ;
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  jint arg2 ;
  std::vector< std::string >::value_type *arg3 = 0 ;
  std::vector< std::string >::value_type result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  arg2 = jarg2; 
  if(!jarg3) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
    return 0;
  }
  const char *arg3_pstr = (const char *)jenv->GetStringUTFChars(jarg3, 0); 
  if (!arg3_pstr) return 0;
  std::vector< std::string >::value_type arg3_str(arg3_pstr);
  arg3 = &arg3_str;
  jenv->ReleaseStringUTFChars(jarg3, arg3_pstr); 
  try {
    result = std_vector_Sl_std_string_Sg__doSet(arg1,SWIG_STD_MOVE(arg2),(std::string const &)*arg3);
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return 0;
  }
  jresult = jenv->NewStringUTF((&result)->c_str()); 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_StringVector_1doRemoveRange(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3) {
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  jint arg2 ;
  jint arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  arg2 = jarg2; 
  arg3 = jarg3; 
  try {
    std_vector_Sl_std_string_Sg__doRemoveRange(arg1,SWIG_STD_MOVE(arg2),SWIG_STD_MOVE(arg3));
  } catch(std::out_of_range &_e) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, (&_e)->what());
    return ;
  }
}


SWIGEXPORT void JNICALL Java_com_hyh_jnitest_basic_infrastructure_FINInfrastructureJNI_delete_1StringVector(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  std::vector< std::string > *arg1 = (std::vector< std::string > *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(std::vector< std::string > **)&jarg1; 
  delete arg1;
}


#ifdef __cplusplus
}
#endif

