//#ifdef INPUT

#include <string>
#include <iostream>
using namespace std;

namespace Planning {
	class Binding;

	template<class T>
	class InputAction {
	public:
		InputAction(std::string a,const Binding& b, bool continous = false);
	};

	class Vector2float;
	class Modifier;

	class Binding
	{
	public:
		Binding& AddModifier(const Modifier& b);
		~Binding()
		{
			std::cout << "Binding free";
		}
	};

	class Binding1D : public Binding
	{
	public:
		Binding1D(const Binding& keyboard_binding, const Binding& keyboard_binding1);
	};

	class Binding2D : public Binding
	{
	public:
		Binding2D(const Binding& _xpositive, const Binding& _xnegative,
			const Binding& _ypositive, const Binding& _ynegative);
	};

	class BindingOR : public Binding
	{
	public:
		BindingOR(const Binding& _a, const Binding& _b);
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
		ModifierHold(float time, bool continous = false);
	};

	class ModifierRepeat : public Modifier
	{
	public:
		ModifierRepeat(int count);
	};


	void main2() {

		new InputAction<float>("Run", Binding1D(KeyboardBinding("W"), KeyboardBinding("S")));

		new InputAction<bool>("Fire", KeyboardBinding("Space"));

		new InputAction<bool>("Charge",
			KeyboardBinding("Q").AddModifier(ModifierHold(0.3))
			);

		new InputAction<Vector2float>("Direction",
			Binding2D(
				KeyboardBinding("W"),
				KeyboardBinding("S"),
				KeyboardBinding("A"),
				KeyboardBinding("D")
			), true);


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

		new InputAction<bool>("Combo", BindingAND(
			InputMapBinding("F"),
			InputMapBinding("G")
		).AddModifier(ModifierHold(0.5, true)
		), true);
	}


}

#endif