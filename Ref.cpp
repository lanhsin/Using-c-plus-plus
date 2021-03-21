#include <cstring>
#include <iostream>

class dsString{
public:
    size_t len_;
    char* str_;
    dsString();
    ~dsString();
    dsString(const char *);
    dsString(const dsString &);
    dsString(dsString &&);
    dsString& operator=(dsString&& s);
};

dsString::dsString(): str_(0), len_(0)
{
  std::cout << "default constructor" << this << std::endl;
}

dsString::~dsString()
{
  std::cout << "destructor:" << this << std::endl;
  delete [] str_;
}

dsString& dsString::operator=(dsString&& s)  // move assignment
{
  std::cout << "move assignment" << this << std::endl;
  str_ = s.str_;
  len_ = s.len_;
  s.str_ = 0;
  s.len_ = 0;
  return *this;
}

dsString::dsString(const char *str)
{
  len_ = strlen(str);
  str_ = new char(len_);
  std::cout << "const char *str constructor " << this << std::endl ;
  memcpy(str_, str, len_);
}

dsString::dsString(dsString &&s)
{
  str_ = s.str_;
  len_ = s.len_;
  s.str_ = 0;
  s.len_ = 0;

  std::cout << "move constructor " << this << std::endl;
}

dsString::dsString(const dsString &s)
{
  std::cout << "copy constructor " << this << std::endl;
  len_ = strlen(s.str_);
  str_ = new char(len_);
  memcpy(str_, s.str_, s.len_);
}

void flvalue(dsString s)
{
  std::cout << "flvalue s: " << s.str_ << std::endl;
}

void flvalueRef(dsString& s)
{
  std::cout << "flvalueRef s: " << s.str_ << std::endl;
}

void fRvalueRef(dsString&& s)
{
  std::cout << "fRvalueRef s: " << s.str_ << std::endl;
}

int main()
{
  dsString s1{"s1"};
  dsString s2{"s2"};
  dsString s3{"s3"};
  flvalue(s1);
  flvalue(std::move(s1));

  flvalueRef(s2);
  //flvalueRef(std::move(s2)); cannot bind non-const lvalue reference  to an rvalue 
  //fRvalueRef(s2);  cannot bind rvalue reference to lvalue 
  fRvalueRef(std::move(s3));
  
  return 0;
}
