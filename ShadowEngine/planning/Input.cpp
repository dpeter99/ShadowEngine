#include <string>
using namespace std;

template<class T>
class InputAction{
    public:
    InputAction(std::string a, ::Binding& b);
};

class Vector2float;
class Modifier;

class Binding
{
public:
	Binding& AddModifier(const ::Modifier& b);
};

class Binding1D: public Binding
{
public:
	Binding1D(const ::Binding& keyboard_binding, const ::Binding& keyboard_binding1);
};

class Binding2D : public Binding 
{
public:
	Binding2D(const ::Binding& _xpositive, const ::Binding& _xnegative,
			const ::Binding& _ypositive, const ::Binding& _ynegative );
};

class BindingOR : public Binding
{
public:
	BindingOR(const ::Binding& _a, const ::Binding& _b);
};

class KeyboardBinding : public Binding {
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

class ModifierRepeat : public Modifier
{
public:
	ModifierRepeat(int count);
};


void main(){

	new InputAction<float>("Run", ::Binding1D(KeyboardBinding("W"), KeyboardBinding("S")));

	new InputAction<bool>("Fire", KeyboardBinding("Space"));

	new InputAction<bool>("Charge",
		KeyboardBinding("Q").AddModifier(ModifierHold(0.3))
		);

	new InputAction<Vector2float>("Direction",
		::Binding2D(
			KeyboardBinding("W"),
			KeyboardBinding("S"),
			KeyboardBinding("A"),
			KeyboardBinding("D")
		));


	new InputAction<bool>("QuickTime",
		KeyboardBinding("Q").AddModifier(ModifierRepeat(5)));

	new InputAction<bool>("Cause", BindingOR(
		KeyboardBinding("R"),
		KeyboardBinding("J")
	));

	new InputAction<float>("Uhhh", BindingOR(
		Binding1D(
			KeyboardBinding("Q"),
			KeyboardBinding("E")
		),
		Binding1D(
			KeyboardBinding("+"),
			KeyboardBinding("-")
		)
	));
}
