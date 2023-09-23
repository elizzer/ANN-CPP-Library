#include "Value.h"

Value::Value(){

}
Value::Value(float data){
    this->data=data;
}
Value::Value(float data,string label){
    // Value(data);
    this->label=label;
}

vector<Value> Value:: getPrev(){
    return this->prev;
}

char Value::getOp(){
    return this->_op;
}

string Value::getLabel(){return this->label;}
double Value::getGrad(){return grad;}
float Value::getData(){return data;}

Value Value::operator*(Value other){
    Value temp(this->data*other.data,this->getLabel()+"*"+other.getLabel());
    return temp;
}

Value Value::operator+(Value other){
    Value temp(this->data+other.data,this->getLabel()+"+"+other.getLabel());
    return temp;
}