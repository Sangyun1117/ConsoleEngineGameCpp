/******************************************************************************
 * RTTI.h
 *
 * ��� ���迡 �ִ� Ŭ���� ���� ��Ÿ�� Ÿ�� Ȯ�� �� ������ ����ȯ�� ����
 * C++�� dynamic_cast�� ��ü�ϰų�, �Ϻ� ȯ�濡�� ���� Ÿ�� üũ�� ���� ���
 *
 ******************************************************************************/

#pragma once
#include "Core.h"

// RunTime-Type-Information.
class Engine_API RTTI
{
public:
	// ���� ���� �Լ�: ��ü�� Ÿ�� ID ��ȯ
	virtual const size_t& TypeIdInstance() const = 0;

	//Ÿ��id�� ��ġ�ϴ��� Ȯ��
	virtual bool Is(const size_t id) const
	{
		return false;
	}

	//������ T Ÿ������ �����ϰ� ĳ����
	template<typename T>
	T* As()
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}

		//Ÿ���� �ٸ��� nullptr ��ȯ
		return nullptr;
	}

	template<typename T>
	const T* As() const
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}

		return nullptr;
	}
};

// ��ũ��: Ŭ���� ���ο� �����Ͽ� RTTI ��� Ȱ��ȭ
#define RTTI_DECLARATIONS(Type, ParentType)												\
public:																					\
	using super = ParentType;															\
    /* ��ü Ÿ�� ID ��ȯ */																\
	virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }		\
	static const size_t TypeIdClass()													\
	{																					\
		static int runTimeTypeId = 0;													\
		return reinterpret_cast<size_t>(&runTimeTypeId);								\
	}																					\
	/* Ư�� Ÿ�� ID�� ��ġ�ϴ��� Ȯ��, ��� ���� ���� �˻� */							\
	virtual bool Is(const size_t id) const												\
	{																					\
		if (id == TypeIdClass())														\
		{																				\
			return true;																\
		}																				\
		else																			\
		{																				\
            /* ���� Ŭ������ Is ȣ���Ͽ� ��� ���� Ȯ�� */								\
			return ParentType::Is(id);													\
		}																				\
	}