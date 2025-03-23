#ifndef JAVA_OBJECT_CONFIG
#define JAVA_OBJECT_CONFIG


%define %java_hash_equals(c_type)

%javamethodmodifiers c_type::calculateHash "private";
%javamethodmodifiers c_type::isEquals "private";

%feature("nodirector") c_type::calculateHash;
%feature("nodirector") c_type::isEquals;

// Java端的代码
%typemap(javacode) c_type %{
  @Override
  public boolean equals(Object obj) {
    if (this == obj) return true;
    if (obj == null || getClass() != obj.getClass()) return false;
    $typemap(jstype, c_type) other = ($typemap(jstype, c_type)) obj;
    return this.isEquals(other);
  }

  @Override
  public int hashCode() {
    return this.calculateHash();
  }
%}

%extend c_type {
  int calculateHash() const {
    return static_cast<int>(std::hash<const c_type*>{}(self));
  }

  bool isEquals(const c_type& other) const {
    return self == &other;
  }
}


%enddef



#endif // JAVA_OBJECT_CONFIG