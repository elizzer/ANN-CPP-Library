// #include<iostream>
// #include<string.h>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

class Value{
    private:
        float data;
        vector <Value> prev;
        char _op='_';
        double grad=0;
        string label;
        bool leafFlag;
    public:
        Value();
        Value(float data);
        // Value(float data, string label);
        Value(float data, string label,bool);

        vector<Value> getPrev();
        char getOp();
        string getLabel();
        double getGrad();
        float getData();
        bool getLeafFlag();

        void setGrad(double grad);
        void setPrev(vector <Value>);
        void setLeafFlag(bool flag);
        void setLabel(string);
        void setOP(char);
        void print();

        Value operator+(Value& other);
        Value operator*(Value& other);


        void backward();
        void backward_call(vector<Value>&,char op);


        Value tanh();
        Value reLu();
        Value step();
        Value linear();
};

Value::Value(){

}
Value::Value(float data){
    this->data=data;
}
Value::Value(float data,string label,bool flag=false){
    this->data=data;
    this->label=label;
    this->leafFlag=flag;
}

vector<Value> Value:: getPrev(){return this->prev;}
char Value::getOp(){return this->_op;}
string Value::getLabel(){return this->label;}
double Value::getGrad(){return grad;}
float Value::getData(){return data;}
bool Value::getLeafFlag(){return leafFlag;}

void Value::setGrad(double grad){this->grad=grad;}
void Value::setPrev(vector <Value> prev){this->prev=prev;}
void Value::setLeafFlag(bool flag){leafFlag=flag;}
void Value::setOP(char op){_op=op;}
void Value::setLabel(string label){this->label=label;}

Value Value::operator*(Value &other){
    Value temp(data*other.data,getLabel()+"*"+other.getLabel());
    vector <Value> prev;
    prev.push_back(*this);
    prev.push_back(other);
    temp.setPrev(prev);
    temp.setOP('*');
    return temp;
}
Value Value::operator+(Value &other){
    Value temp(this->data+other.data,this->getLabel()+"+"+other.getLabel());
    vector <Value> prev;
    prev.push_back(*this);
    prev.push_back(other);
    temp.setPrev(prev);
    temp.setOP('+');
    return temp;
}

Value Value::step(){
    float val=this->data;
    if(val>0.5){
        val=1;
    }else{
        val=0;
    }
    Value temp(val,"step("+label+")");
    vector <Value>prev;
    prev.push_back(*this);
    temp.setPrev(prev);
    temp.setOP('s');
    return temp;
}
Value Value::reLu(){
    float val=data;
    if(data<=0){
        val=0;
    }
    Value temp(val,"reLu("+label+")");
    vector <Value>prev;
    prev.push_back(*this);
    temp.setPrev(prev);
    temp.setOP('r');
    return temp;
}
Value Value::tanh(){
    Value temp(std::tanh(data),"tanh("+label+")");
    vector <Value>prev;
    prev.push_back(*this);
    temp.setPrev(prev);
    temp.setOP('t');
    return temp;
}
void Value::backward_call(vector<Value> &prev,char op){
    switch (op)
    {
    case '+':
        prev[0].setGrad(prev[0].getGrad()+grad);
        prev[1].setGrad(prev[1].getGrad()+grad);
        break;
    case '*':
        prev[0].setGrad(prev[0].getGrad()+prev[1].getData()*grad);
        prev[1].setGrad(prev[1].getGrad()+prev[0].getData()*grad);
        break;
    case 't':
        prev[0].setGrad(prev[0].getGrad()+(1-pow(std::tanh(data),2))*grad);
        break;
    case 'r':
        if(data<=0){
            prev[0].setGrad(prev[0].getGrad());
        }else{
            prev[0].setGrad(prev[0].getGrad()+grad);
        }
    default:
        break;
    }

}

void Value::print(){
    string p1=(prev.size() > 0) ?prev[0].getLabel():"_";
    string p2=(prev.size() > 1) ?prev[1].getLabel():"_";
    cout<<"\n Label:"+label+" Value:"<<data<<" Grad:"<<grad<<" prev_lables:"<<p1<<" "<<p2<<" OP:"<<_op;
}

void Value::backward(){
    print();
    if(prev.size()==0){
        return;
    }
    backward_call(prev,_op);
    for (Value prev :this->prev){
        prev.backward();
    }

}


/***
o-> should update the prev grads based on the operation
push prev into the stack 

*/