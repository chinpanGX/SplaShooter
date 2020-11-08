/*-----------------------------------------------------------

	[Component.h]
	コンポーネント
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once

class Component
{
protected:
	unsigned int m_Id = -1; // ID
public:
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};
	// Getter / Setter
	Component* GetComponet()
	{
		return this;
	}
	
	int GetID()
	{
		return m_Id;
	}

	void SetID(int id)
	{
		m_Id = id;
	}
	
	template <class T>
	T* GetComponet()
	{
		if (typeid(*this) == typeid(T))
		{
			return *this;
		}
	}
};