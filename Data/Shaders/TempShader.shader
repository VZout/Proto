<ShaderProgram name="DebugRender">
	<VertexShader language="glsl" api="opengles" attributes="in_Position">
		attribute vec3 in_Position;
		attribute vec4 in_Color;

		varying vec4 a_Color;
		void main()
		{
			a_Color = in_Color;
			gl_Position = vec4(in_Position, 1.0);
		} 
 	</VertexShader>

	<PixelShader language="glsl" api="opengles">
		precision mediump float;

		varying vec4 a_Color;

		void main()
		{
			gl_FragColor = a_Color;
		}
	</PixelShader>

	<VertexShader language="glsl" api="opengl">
		#version 430 core

		in vec3 in_Position;
		in vec4 in_Color;

		out vec4 a_Color;

		void main(void)
		{
			a_Color = in_Color;
		    gl_Position = vec4(in_Position, 1.0);
		}
	</VertexShader>

	<PixelShader language="glsl" api="opengl">
		#version 430 core

		in vec4 a_Color;

		out vec4 out_Color;

		void main(void)
		{
		      out_Color = a_Color;
		}
	</PixelShader>
	
	<VertexShader language="hlsl" entrypoint="VSMain" api="dx11">
		struct PSInput
		{
			float4 position : SV_POSITION;
			float4 color : COLOR;
		};

		PSInput VSMain(float4 position : POSITION, float4 color : COLOR)
		{
			PSInput result;
			result.position = position;
			result.color = color;
			return result;
		}
	</VertexShader>

	<PixelShader language="hlsl" entrypoint="PSMain" api="dx11">
		struct PSInput
		{
			float4 position : SV_POSITION;
			float4 color : COLOR;
		};

		float4 PSMain(PSInput input) : SV_TARGET
		{
			return input.color;
		}
	</PixelShader>

	<VertexShader language="hlsl" entrypoint="VSMain" api="dx12">
		struct PSInput
		{
			float4 position : SV_POSITION;
			float4 color : COLOR;
		};

		PSInput VSMain(float4 position : POSITION, float4 color : COLOR)
		{
			PSInput result;
			result.position = position;
			result.color = color;
			return result;
		}
	</VertexShader>

	<PixelShader language="hlsl" entrypoint="PSMain" api="dx12">
		struct PSInput
		{
			float4 position : SV_POSITION;
			float4 color : COLOR;
		};

		float4 PSMain(PSInput input) : SV_TARGET
		{
			return input.color;
		}
	</PixelShader>
</ShaderProgram>