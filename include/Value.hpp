#ifndef _PANTHER_VALUE_
#define _PANTHER_VALUE_
#include <iostream>

namespace PantherExpress {
  template<typename T>
  class Value {
    private:
      T data;
    
    public:
      Value(T data) {
        this->data = data;
      }

      friend std::ostream& operator<<(std::ostream& stream, const Value& value) {
          stream << value.data;
          return stream;
      }
  };
}

#endif
