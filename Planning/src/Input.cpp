#include <string>
using namespace std;

class Binding;

template<class T>
class InputAction {
public:
	InputAction(std::string a, Binding* b);
};

class Vector2float;
class Modifier;

class Binding
{
public:
	Binding* AddModifier(const ::Modifier* b);
};

class Binding1D : public Binding
{
public:
	Binding1D(Binding* _xpositive, Binding* _xnegative);
};

class Binding2D : public Binding
{
public:
	Binding2D(const ::Binding* _xpositive, const ::Binding* _xnegative,
		const ::Binding* _ypositive, const ::Binding* _ynegative);
};

class BindingOR : public Binding
{
public:
	BindingOR(const ::Binding* _a, const ::Binding* _b);
};

class BindingAND : public Binding
{
public:
	BindingAND(const Binding& _a, const Binding& _b);
};

class KeyboardBinding : public Binding {
public:
	KeyboardBinding(const char* str);
};

class InputMapBinding : public Binding
{
public:
	InputMapBinding(const char* map);
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


void main() {

	new InputAction<float>("Run", new Binding1D(new KeyboardBinding("W"), new KeyboardBinding("S")));

	new InputAction<bool>("Fire", new KeyboardBinding("Space"));

	new InputAction<bool>("Charge",
		(new KeyboardBinding("Q"))->AddModifier(new ModifierHold(0.3))
		);

	new InputAction<Vector2float>("Direction",
		new Binding2D(
			new KeyboardBinding("W"),
			new KeyboardBinding("S"),
			new KeyboardBinding("A"),
			new KeyboardBinding("D")
		));


	new InputAction<bool>("QuickTime",
		(new KeyboardBinding("Q"))->AddModifier(new ModifierRepeat(5)));

	new InputAction<bool>("Cause", new BindingOR(
		new KeyboardBinding("R"),
		new KeyboardBinding("J")
	));

	new InputAction<float>("Uhhh", new BindingOR(
		new Binding1D(
			new KeyboardBinding("Q"),
			new KeyboardBinding("E")
		),
		new Binding1D(
			new KeyboardBinding("+"),
			new KeyboardBinding("-")
		)
	));


	new InputAction<bool>("Combo", BindingAND(
		InputMapBinding("F"),
		InputMapBinding("G")
	).AddModifier(ModifierHold(0.5, true)
	), true);
}
