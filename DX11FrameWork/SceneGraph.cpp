//-----------------------------------------------------------------------------
// File: SceneGraph.cpp
// Description : This Class managers the Scene
//-----------------------------------------------------------------------------

#include "SceneGraph.h"

//-----------------------------------------------------------------------------
// Name: SceneGraph()
// Desc: Constructor
//-----------------------------------------------------------------------------
SceneGraph::SceneGraph(void)
{
}

//-----------------------------------------------------------------------------
// Name: SceneGraph()
// Desc: Constructor
//-----------------------------------------------------------------------------
SceneGraph::SceneGraph(ID3D11Device* device, ID3D11DeviceContext* deviceContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* renderTarget)
{
	this->m_device = device;
	this->m_deviceContext = deviceContext;
	this->m_renderTarget = renderTarget;
	this->m_swapChain = swapChain;
}

//-----------------------------------------------------------------------------
// Name: ~SceneGraph()
// Desc: Destructor
//-----------------------------------------------------------------------------
SceneGraph::~SceneGraph(void)
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Render all the objects within the scene
//-----------------------------------------------------------------------------
HRESULT SceneGraph::Render(void)
{
	if( NULL == this->m_device )
	{
		return E_FAIL;
	}

	// Clear the screen to black
	float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	this->m_deviceContext->ClearRenderTargetView(this->m_renderTarget, clearColor);

	// Any rendering code goes here

	SceneNode* _collision1 = NULL;
	SceneNode* _collision2 = NULL;

	for (unsigned int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->Update();
		_nodes[i]->Render();

		if(_nodes[i]->ReturnName() == L"boundingBox")
		{
			if (_collision1 == NULL)
			{
				_collision1 = _nodes[i];
			}
			else
			{
				_collision2 = _nodes[i];

				//// Check to see if the tank is colliding with the objects
				//if (_collision1->IsIntersecting(_collision2))
				//{
				//	XMFLOAT3 _direction = XMFLOAT3(0.0f, 0.0f, 5.0f);
				//	if (_collision1->CheckDirectionZ())
				//	{
				//		_nodes[4]->SetPosition(_direction * -1);
				//	}
				//	else
				//	{
				//		_nodes[4]->SetPosition(_direction);
				//	}
				//}
			}
		}
		else if(_nodes[i]->ReturnName() == L"boundingSphere")
		{
			// Check the bullets aginst the Castle & Crate
			if (_nodes[i]->IsIntersecting(_nodes[5]) || _nodes[i]->IsIntersecting(_nodes[12]))
			{
				_nodes[i+1]->ExternalDeleteMe(true);
			}
		}

		if(_nodes[i]->DeleteMe() == true)
		{
			RemoveNode(i);
		}
		
	}

//	_camera->Update();
//_camera->Render();


	// Show the back buffer in the window
	this->m_swapChain->Present(0, 0);



/*
	// Begin the scene
//	if( SUCCEEDED( _pd3dDevice->BeginScene() ) )
	if( SUCCEEDED( _device->BeginScene() ) )
	{
		SceneNode* _collision1 = NULL;
		SceneNode* _collision2 = NULL;

		for (unsigned int i = 0; i < _nodes.size(); i++)
		{
			_nodes[i]->Update();
			_nodes[i]->Render();

			if(_nodes[i]->ReturnName() == L"boundingBox")
			{
				if (_collision1 == NULL)
				{
					_collision1 = _nodes[i];
				}
				else
				{
					_collision2 = _nodes[i];

					// Check to see if the tank is colliding with the objects
					if (_collision1->IsIntersecting(_collision2))
					{
						XMVECTOR _direction = XMVECTOR(0.0f, 0.0f, 5.0f);
						if (_collision1->CheckDirectionZ())
						{
							_nodes[4]->SetPosition(_direction * -1);
						}
						else
						{
							_nodes[4]->SetPosition(_direction);
						}
					}
				}
			}
			else if(_nodes[i]->ReturnName() == L"boundingSphere")
			{
				// Check the bullets aginst the Castle & Crate
				if (_nodes[i]->IsIntersecting(_nodes[5]) || _nodes[i]->IsIntersecting(_nodes[12]))
				{
					_nodes[i+1]->ExternalDeleteMe(true);
				}
			}

			if(_nodes[i]->DeleteMe() == true)
			{
				RemoveNode(i);
			}
		}

		_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	_pd3dDevice->Present( NULL, NULL, NULL, NULL );
*/

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Initialise()
// Desc: Initialise the SceneGraph
//-----------------------------------------------------------------------------
HRESULT SceneGraph::Initialise(void)
{
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: OnLostDevice()
// Desc: Has the Device been lost
//-----------------------------------------------------------------------------
void SceneGraph::OnLostDevice(void)
{

}

//-----------------------------------------------------------------------------
// Name: OnResetDevice()
// Desc: Resets the Device()
//-----------------------------------------------------------------------------
void SceneGraph::OnResetDevice(void)
{

}

//-----------------------------------------------------------------------------
// Name: Update()
// Desc: Updates all of the objects within the scene
//-----------------------------------------------------------------------------
void SceneGraph::Update(void)
{
	for (unsigned int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->Update();
	}
}

//-----------------------------------------------------------------------------
// Name: Shutdown()
// Desc: Perform cleanup
//-----------------------------------------------------------------------------
void SceneGraph::Shutdown(void)
{
	for (unsigned int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->Shutdown();
	}

	if (_nodes.size() != 0)
	{
		_nodes.clear();
	}

	if (_nodes.size() != 0)
	{
		_nodes.clear();
	}
}

//-----------------------------------------------------------------------------
// Name: AddNode()
// Desc: Adds a new node to the collection
//-----------------------------------------------------------------------------
bool SceneGraph::AddNode(SceneNode* node, wstring parentNode)
{
	wstring _string = L"Parent";

	if (_string.compare(parentNode)== 0)
	{
		_nodes.insert(_nodes.end(), node);
	}
	else
	{
		_nodes[0]->AddChild(node);
	}
	return 0;
}

//-----------------------------------------------------------------------------
// Name: RemoveNode()
// Desc: Removes a Node from the collection
//-----------------------------------------------------------------------------
bool SceneGraph::RemoveNode(unsigned int node)
{
	if (node <= _nodes.size())
	{
		_nodes.erase(_nodes.begin() + (node));
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
// Name: FindNode()
// Desc: Searches for a SceneNode by name & returns an integer
//-----------------------------------------------------------------------------
int SceneGraph::FindANode(wstring name)
{
	for (unsigned int i = 0; i < _nodes.size(); i++)
	{
		if(_nodes[i]->ReturnName() == name)
		{
			return i;
		}
	}
	return 0;
}


//-----------------------------------------------------------------------------
// Name: FindNode()
// Desc: Searches for a SceneNode by name
//-----------------------------------------------------------------------------
SceneNode* SceneGraph::FindNode(wstring name)
{
	for (unsigned int i = 0; i < _nodes.size(); i++)
	{
		if(_nodes[i]->ReturnName() == name)
		{
			return _nodes[i];
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------
// Name: FindNode()
// Desc: Searches for a SceneNode by node
//-----------------------------------------------------------------------------
SceneNode* SceneGraph::FindNode(SceneNode* nodeToFind)
{
	for (unsigned int i = 0; i < _nodes.size(); i++)
	{
		if(nodeToFind == _nodes[i])
		{
			return _nodes[i];
		}
	}
	return 0;
}


void SceneGraph::SetCamera(Camera* camRender)
{
	_camera = camRender;
}
