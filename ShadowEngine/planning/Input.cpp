#include <string>
using namespace std;

template<class T>
class InputAction{
    public:
    InputAction(std::string a, ::Binding& b);
};

class Vector2float;
class Modifier;

class Binding{
public:
	Binding& AddModifier(const ::Modifier& b);
};

class Binding2D: public Binding{
public:
	Binding2D(const ::Binding& keyboard_binding, const ::Binding& keyboard_binding1);
};

class KeyboardBinding : public Binding{
public:
	KeyboardBinding(const char* str);
};

class Modifier
{
	
};

class ModifierHold : public Modifier
{
public:
	ModifierHold(float time);
};


void main(){

	new InputAction<Vector2float>("Run", ::Binding2D(KeyboardBinding("W"), KeyboardBinding("S")));
	new InputAction<bool>("Fire", KeyboardBinding("Space"));
	new InputAction<bool>("Charge",
		KeyboardBinding("Q").AddModifier(ModifierHold(0.3))
		);


}