#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
#include "../../ShadowEngine/dependencies/glm/glm/vec4.hpp"
#include "../../ShadowEngine/dependencies/glm/glm/mat4x4.hpp"


namespace ShadowEngine {

	/**
	 * \brief This is the base class for every class in the Engine that uses runtime reflection.
	 */
	class SHObject
	{
	protected:
		/**
		 * \brief Generates a new UID for each call
		 * \return Unique ID
		 */
		static uint64_t GenerateId() noexcept
		{
			static uint64_t count = 0;
			return ++count;
		}

	public:
		/**
		 * \brief Returns the top level class type name of the object
		 * \return Class name string
		 */
		virtual const std::string& GetType() const = 0;
		/**
		 * \brief Gets the top level type ID
		 * \return UID of the class
		 */
		virtual const uint64_t GetTypeId() const = 0;

		virtual ~SHObject() = default;
	};


	/**
	 * \brief Macro to make the override functions of SHObject. This should be added in each derived class
	 * \param type The type of the class
	 */
#define SHObject_Base(type)	\
public: \
	static const std::string& Type()				{ static const std::string t = typeid(type).name(); return t; } \
	static uint64_t TypeId()						{ static const uint64_t id = GenerateId(); return id; } \
	const std::string& GetType() const override		{ return Type();  } \
	const uint64_t GetTypeId() const override		{ return  type::TypeId(); } \
private:

}

namespace ShadowEngine::Rendering {
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			D3D12 = 2
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		//virtual void Draw(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform = glm::mat4(1.0f)) =0;
		virtual void Draw(const void* mesh, const void* shader, const void* materialData) = 0;

		/**
		 * \brief Starts recording the draw commands
		 */
		virtual  void StartFrame() = 0;

		/**
		 * \brief Finalizes the render command recording
		 */
		virtual void EndFrame() = 0;

		virtual void StartResourceUpload() = 0;


		inline static API GetAPI() { return s_API; }

		static RendererAPI* RendererAPI::MakeRendererAPI();
	private:
		static API s_API;
	};

}

class Resource : public ShadowEngine::SHObject
{
	SHObject_Base(Resource)
	
public:
	std::string name;

	Resource(std::string name):name(name) {  }

	virtual bool operator==(const Resource& rhs)
	{
		return this->name == rhs.name;
	}
};



struct RenderTargetSize
{
	enum Type
	{
		Specific,
		SwapChainDependent
	};

	Type t;
	
	int w;
	int h;

	RenderTargetSize(Type t, int w, int h): t(t), w(w),h(h) {  }

	RenderTargetSize(std::initializer_list<int> data)
	{
		h = *data.begin();
		w = (data.begin()[1]);
	}

	bool operator==(const RenderTargetSize& other)
	{
		return
			this->t == other.t &&
			this->w == other.w &&
			this->h == other.h;
	}
	
	static RenderTargetSize SWAP_CHAIN;
};

RenderTargetSize RenderTargetSize::SWAP_CHAIN = RenderTargetSize(SwapChainDependent, -1, -1);

class RenderTargetTexture: public Resource
{
	SHObject_Base(RenderTargetTexture)
	
private:
	RenderTargetSize size;

public:
	enum Access
	{
		Read,
		Write,
		Read_Write
	};

	Access acces;
	
public:
	RenderTargetTexture(std::string name, RenderTargetSize size, Access access)
		: Resource(name),
			size(size),
		  acces(access)
	{
	}

	~RenderTargetTexture() override{}
	
	bool operator==(const Resource& rhs) override
	{
		return
			this->GetTypeId() == rhs.GetTypeId() &&
			this->name == rhs.name &&
			this->size == static_cast<const RenderTargetTexture&>(rhs).size;
	}
	
	
};



class Camera
{
	
};

class Node
{
	
};

class Scene
{
public:
	std::vector<Node> nodes;

	std::vector<Camera> cameras;
	std::vector<Node> CullObjects(const Camera& camera)
	{
		return nodes;
	}
};


class Context
{
public:

	glm::mat4 viewProjection;

	void SetCamera(Camera c){}
	void DrawNode(Node& node)
	{
		
	}
};



/**
 * A render pass
 *
 * Inputs:
 *
 *
 * Outputs:
 *
 * 
 *
 * \brief 
 */
class RenderPass
{
protected:
    std::vector<Resource> Inputs;

    std::vector<Resource> Output;
public:
    virtual void Register() = 0;
	
    virtual void Setup() = 0;

    virtual void Run(Context ctx, Scene& scene) = 0;

public:
	std::vector<Resource>& getInputResources()
	{
		return Inputs;
	}
};

class GraphicsPipelineBuider
{

	std::vector<RenderPass*> passes;

	std::vector<Resource> resources;

public:
	void addPass(RenderPass* pass)
	{
		passes.push_back(pass);
	}

	void build()
	{
		for (int i = 0; i < passes.size(); ++i)
		{
			passes[i]->Register();
			
			auto& Inputs = passes[i]->getInputResources();

			//Find the reused resources
			for (auto & input : Inputs)
			{
				bool added = false;
				
				for (auto & resource : resources)
				{
					//check if the resources are the same
					if(input == resource)
					{
						//We already have it in the list
					}
					else
					{
						resources.push_back(input);
						added = true;
					}
				}

				if (!added)
					resources.push_back(input);
			}

			
		}
	}
	
};



class PostProcess : public RenderPass
{
	void Register() override
	{
		Inputs.push_back(RenderTargetTexture("final", RenderTargetSize::SWAP_CHAIN, RenderTargetTexture::Write));
		Output.push_back(RenderTargetTexture("final", RenderTargetSize::SWAP_CHAIN, RenderTargetTexture::Write));
	}

	void Setup() override
	{


	}

	void Run(Context ctx, Scene& scene) override
	{
		//Run the shader on the full screen quad
	}
};

class BasicRenderPass : public RenderPass
{
	void Register() override
	{
		Output.push_back(RenderTargetTexture("final", { 2048,2048 }, RenderTargetTexture::Write));
	}

	void Setup() override
	{


	}

	void Run(Context ctx, Scene& scene) override
	{
		for (auto& camera : scene.cameras)
		{
			//Set the camera to be used
			ctx.SetCamera(camera);

			//Cull the objects
			auto objects = scene.CullObjects(camera);

			for (int i = 0; i < objects.size(); ++i)
			{
				//Draw each
				ctx.DrawNode(objects[i]);
			}
		}		
	}
};


class BasicRenderGraph
{
public:
	void Register(GraphicsPipelineBuider& builder)
	{
		builder.addPass(new BasicRenderPass());
		builder.addPass(new PostProcess());
	}
};


void main()
{
	GraphicsPipelineBuider builder;


	BasicRenderGraph grpah;
	
	grpah.Register(builder);

	builder.build();

	std::cout << "ASD";
}