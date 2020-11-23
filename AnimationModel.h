#pragma once
//AnimationModel.h

#include <map>
#include <vector>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

#pragma comment (lib,"assimp.lib")

#include "DirectX11.h"

struct DEFORM_VERTEX
{
	aiVector3D	Position;
	aiVector3D	Normal;

	int			BoneNum;
	std::string	BoneName[4];		//�{���̓{�[���C���f�b�N�X�ŊǗ�����ׂ�
	float		BoneWeight[4];
};

//�{�[���\����
struct BONE
{
	aiMatrix4x4	Matrix;
	aiMatrix4x4	AnimationMatrix;
	aiMatrix4x4	OffsetMatrix;
};

class AnimationModel
{
private:
	const aiScene* m_Scene = NULL;			 //assimp�̓ǂݍ��݂ɕK�v
	std::map<std::string, const aiScene*> m_Animation;


	ID3D11Buffer** m_VertexBuffer;			//�����K�v�ɂȂ�̂�**(�_�u���|�C���^�[)
	ID3D11Buffer** m_IndexBuffer;

	std::map<std::string, ID3D11ShaderResourceView*> m_Texture;

	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

	std::vector<DEFORM_VERTEX>* m_DeformVertex;	 //�ό`�㒸�_�f�[�^
	std::map<const std::string, BONE> m_Bone;	//�{�[���f�[�^(���O�ŎQ��)
public:
	void Load(Wrapper::DirectX11& dx, const char* FileName);
	void LoadAnimation(const char* FileName, const char* Name);
	void Unload();
	void Update(Wrapper::DirectX11& dx, const char* AnimationName1, const char* AnimationName2, float BlendRate, int Frame);
	void Draw(Wrapper::DirectX11& dx);
};

