///
/// @file 	vector_t.h 
/// @brief	C++ library
/// @details 	Minimal vector library as some platforms don't include it
/// @n
/// @n @a 	Member of Serial_LCD Library Suite
/// @n @a 	for 4D Systems uLCD-uLED-uVGA screens
/// @n @a 	on Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a 		Developed with [embedXcode](http://embedXcode.weebly.com)
/// 
/// @author 	Rei VILO
/// @author 	http://embeddedcomputing.weebly.com
/// @date	Sep 01, 2012
/// @version 	release 303
/// @n
/// @copyright	© Rei VILO, 2010-2012
/// @copyright	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see	Container for objects like C++ vector
/// @n		http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1289151491
///

#ifndef _VECTOR_T_H
#define _VECTOR_T_H

template<typename Data>
class Vector_t {
  size_t d_size; // Stores number of actually stored objects
  size_t d_capacity; // Stores allocated capacity
  Data *d_data; // Stores data
  
public:
  Vector_t() : 
  d_size(0), d_capacity(0), d_data(0) {
  }; // Default constructor
  
  Vector_t(Vector_t const &other) : 
  d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { 
    d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
    memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
  }; // Copy constuctor
  
  ~Vector_t() { 
    free(d_data); 
  }; // Destructor
  
  Vector_t &operator=(Vector_t const &other) { 
    free(d_data); 
    d_size = other.d_size; 
    d_capacity = other.d_capacity; 
    d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
    memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
    return *this; 
  }; // Needed for memory management
  
  void push_back(Data const &x) { 
    if (d_capacity == d_size) resize(); 
    d_data[d_size++] = x; 
  }; // Adds new value. If needed, allocates more space
  
  size_t size() const { 
    return d_size; 
  }; // Size getter
  
  Data const &operator[](size_t idx) const { 
    return d_data[idx]; 
  }; // Const getter
  
  Data &operator[](size_t idx) { 
    return d_data[idx]; 
  }; // Changeable getter
  
private:
  void resize() { 
    d_capacity = d_capacity ? d_capacity*2 : 1; 
    Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); 
    memcpy(newdata, d_data, d_size * sizeof(Data)); 
    free(d_data); 
    d_data = newdata; 
  }; // Allocates double the old space
}; 


#endif // _VECTOR_T_H not defined


