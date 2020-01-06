
#include <memory>

class Property
{
	int a;
public:
	void* GetPointer()
	{
		return &a;
	}
	void SetValue(int b) { a = b; }
	int GetSize() { return sizeof(int); }
};

class CBImpl
{
public:
	virtual void Update(void* data, int size) = 0;
};

class Dx12CBImpl : public CBImpl
{
	char mappedPtr[10];
public:
	void Update(void* data, int size) override
	{
		memcpy(mappedPtr, data, size);
	}
};

class CB
{
protected:
	std::unique_ptr<CBImpl> impl;
public:
	CB()
	{
		impl = std::make_unique<Dx12CBImpl>();
	}
	
	virtual void Update() = 0;
};

class CBProperty : CB
{
	std::shared_ptr<Property> prop;
public:
	CBProperty(std::shared_ptr<Property> p):prop(p){}
	
	virtual void Update() override
	{
		impl->Update(prop->GetPointer(), prop->GetSize());
	}
};

template<class T>
class CBTyped : CB
{
	T t_data;
public:
	virtual void Update() override
	{
		impl->Update(&t_data, sizeof(T));
	}

	T& operator=(const T& rhs) {
		t_data = rhs;
		return t_data;
	}

	T* operator->() {
		return &t_data;
	}
};

void main2()
{
	std::shared_ptr<Property> p = std::make_shared<Property>();
	p->SetValue(42);

	CBProperty cb_p(p);
	cb_p.Update();

	CBTyped<long> cb_float;
	cb_float = 10;
	cb_float.Update();


	__debugbreak();
}