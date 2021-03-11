/*---------------------------------------------------------

	[AnimationModel.cpp]
	Author : 太田朋希

----------------------------------------------------------*/
#include "AnimationModel.h"

void AnimationModel::Load(Wrapper::DirectX11& dx, const char* FileName)
{
	const std::string modelPath(FileName);

	//ファイル読み込み
	m_Scene = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
	assert(m_Scene);

	//頂点バッファとインデックスバッファの配列を用意する
	m_VertexBuffer = new ID3D11Buffer*[m_Scene->mNumMeshes];
	m_IndexBuffer = new ID3D11Buffer*[m_Scene->mNumMeshes];

	//変形後頂点配列生成
	m_DeformVertex = new std::vector<DEFORM_VERTEX>[m_Scene->mNumMeshes];

	//再帰的にボーン生成
	CreateBone(m_Scene->mRootNode);

	for (unsigned int m = 0; m < m_Scene->mNumMeshes; m++)
	{
		aiMesh* mesh = m_Scene->mMeshes[m];

		//頂点バッファ生成
		{
			Wrapper::VERTEX_3D* vertex = new Wrapper::VERTEX_3D[mesh->mNumVertices];

			for (unsigned int v = 0; v < mesh->mNumVertices; v++)
			{
				vertex[v].Position = D3DXVECTOR3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
				vertex[v].Normal = D3DXVECTOR3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
				vertex[v].TexCoord = D3DXVECTOR2(mesh->mTextureCoords[0][v].x, /*1.0f - */mesh->mTextureCoords[0][v].y);
				vertex[v].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			}

			//頂点バッファ生成
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(Wrapper::VERTEX_3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;

			dx.GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer[m]);

			delete[] vertex;
		}

		//インデックスバッファ生成
		{
			unsigned int* index = new unsigned int[mesh->mNumFaces * 3];

			for (unsigned int f = 0; f < mesh->mNumFaces; f++)
			{
				const aiFace* face = &mesh->mFaces[f];

				assert(face->mNumIndices == 3);

				index[f * 3 + 0] = face->mIndices[0];
				index[f * 3 + 1] = face->mIndices[1];
				index[f * 3 + 2] = face->mIndices[2];
			}

			//インデックスバッファ生成
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned int) * mesh->mNumFaces * 3;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;

			dx.GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer[m]);

			delete[] index;
		}

		//変形後頂点データ初期化
		for (unsigned int v = 0; v < mesh->mNumVertices; v++)
		{
			DEFORM_VERTEX deformVertex;
			deformVertex.Position = mesh->mVertices[v];
			deformVertex.Normal = mesh->mNormals[v];
			deformVertex.BoneNum = 0;

			for (unsigned int b = 0; b < 4; b++)
			{
				deformVertex.BoneName[b] = "";
				deformVertex.BoneWeight[b] = 0.0f;
			}
			m_DeformVertex[m].push_back(deformVertex);
		}

		//ボーンデータ初期化
		for (unsigned int b = 0; b < mesh->mNumBones; b++)
		{
			aiBone* bone = mesh->mBones[b];
			m_Bone[bone->mName.C_Str()].OffsetMatrix = bone->mOffsetMatrix;

			//変形後にボーンデータ格納(骨と頂点データの関連付け)
			for (unsigned int w = 0; w < bone->mNumWeights; w++)
			{
				aiVertexWeight weight = bone->mWeights[w];

				int num = m_DeformVertex[m][weight.mVertexId].BoneNum;

				m_DeformVertex[m][weight.mVertexId].BoneWeight[num] = weight.mWeight;
				m_DeformVertex[m][weight.mVertexId].BoneName[num] = bone->mName.C_Str();
				m_DeformVertex[m][weight.mVertexId].BoneNum++;

				//一つの頂点辺りのボーン数が4つを超えたらエラー
				assert(m_DeformVertex[m][weight.mVertexId].BoneNum <= 4);
			}
		}
	}

	for (unsigned int m = 0; m < m_Scene->mNumMeshes; m++)
	{
		//テクスチャ読み込み
		{
			aiString path;

			if (m_Scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				if (path.data[0] == '*')
				{
					//FBXファイル内から読み込み
					if (m_Texture[path.data] == NULL)
					{
						ID3D11ShaderResourceView* texture;
						int id = atoi(&path.data[m]);

						D3DX11CreateShaderResourceViewFromMemory(
							dx.GetDevice(),
							(const unsigned char*)m_Scene->mTextures[id]->pcData,
							m_Scene->mTextures[id]->mWidth,
							NULL,
							NULL,
							&texture,
							NULL);

						m_Texture[path.data] = texture;
					}
				}
				else
				{
					//外部ファイルから読み込み
				}
			}
			else
			{
				//テクスチャがなかった時の処理(まああり得ない)
				m_Texture[path.data] = NULL;
			}
		}
	}
}

void AnimationModel::LoadAnimation(const char* FileName, const char* Name)
{
	m_Animation[Name] = aiImportFile(FileName, aiProcess_ConvertToLeftHanded);
	assert(m_Animation[Name]);
}

void AnimationModel::Unload()
{
	for (unsigned int m = 0; m < m_Scene->mNumMeshes; m++)
	{
		m_VertexBuffer[m]->Release();
		m_IndexBuffer[m]->Release();
	}

	delete[] m_VertexBuffer;
	delete[] m_IndexBuffer;

	for (std::pair<const std::string, ID3D11ShaderResourceView*> pair : m_Texture)
	{
		pair.second->Release();
	}

	for (std::pair<std::string, const aiScene*> anim : m_Animation)
	{
		aiReleaseImport(anim.second);
	}

	aiReleaseImport(m_Scene);
}

void AnimationModel::Update(Wrapper::DirectX11& dx, const char* AnimationName1, const char* AnimationName2, float BlendRate, int Frame)
{
	//エラー処理
	if (!m_Animation[AnimationName1]->HasAnimations())
		return;
	if (!m_Animation[AnimationName2]->HasAnimations())
		return;

	//アニメーションデータからボーンマトリクス算出
	aiAnimation* animation1 = m_Animation[AnimationName1]->mAnimations[0];
	aiAnimation* animation2 = m_Animation[AnimationName2]->mAnimations[0];

	for (unsigned int c = 0; c < animation1->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim1 = animation1->mChannels[c];
		aiNodeAnim* nodeAnim2 = animation2->mChannels[c];
		BONE* bone = &m_Bone[nodeAnim1->mNodeName.C_Str()];

		int f;
		f = Frame % nodeAnim1->mNumRotationKeys;	//簡易実装
		aiQuaternion rot1 = nodeAnim1->mRotationKeys[f].mValue;

		f = Frame % nodeAnim1->mNumPositionKeys;	//簡易実装
		aiVector3D pos1 = nodeAnim1->mPositionKeys[f].mValue;

		f = Frame % nodeAnim2->mNumRotationKeys;	//簡易実装
		aiQuaternion rot2 = nodeAnim2->mRotationKeys[f].mValue;

		f = Frame % nodeAnim2->mNumPositionKeys;	//簡易実装
		aiVector3D pos2 = nodeAnim2->mPositionKeys[f].mValue;

		aiVector3D pos = pos1 * (1.0f - BlendRate) + pos2 * BlendRate;//線形補間
		aiQuaternion rot;
		aiQuaternion::Interpolate(rot, rot1, rot2, BlendRate);//球面線形補間

		bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
	}

	//再帰的にボーンマトリクスを更新
	UpdateBoneMatrix(m_Scene->mRootNode, aiMatrix4x4());


	//頂点変換(CPUスキニング)
	for (unsigned int m = 0; m < m_Scene->mNumMeshes; m++)
	{
		aiMesh* mesh = m_Scene->mMeshes[m];

		D3D11_MAPPED_SUBRESOURCE ms;
		dx.GetDeviceContext()->Map(m_VertexBuffer[m], 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

		Wrapper::VERTEX_3D* vertex = (Wrapper::VERTEX_3D*)ms.pData;

		for (unsigned int v = 0; v < mesh->mNumVertices; v++)
		{
			DEFORM_VERTEX* deformVertex = &m_DeformVertex[m][v];

			aiMatrix4x4 matrix[4];
			aiMatrix4x4 outMatrix;
			matrix[0] = m_Bone[deformVertex->BoneName[0]].Matrix;
			matrix[1] = m_Bone[deformVertex->BoneName[1]].Matrix;
			matrix[2] = m_Bone[deformVertex->BoneName[2]].Matrix;
			matrix[3] = m_Bone[deformVertex->BoneName[3]].Matrix;

			//ウェイトを考慮してマトリクス算出
			{
				outMatrix.a1 = matrix[0].a1 * deformVertex->BoneWeight[0]
					+ matrix[1].a1 * deformVertex->BoneWeight[1]
					+ matrix[2].a1 * deformVertex->BoneWeight[2]
					+ matrix[3].a1 * deformVertex->BoneWeight[3];

				outMatrix.a2 = matrix[0].a2 * deformVertex->BoneWeight[0]
					+ matrix[1].a2 * deformVertex->BoneWeight[1]
					+ matrix[2].a2 * deformVertex->BoneWeight[2]
					+ matrix[3].a2 * deformVertex->BoneWeight[3];

				outMatrix.a3 = matrix[0].a3 * deformVertex->BoneWeight[0]
					+ matrix[1].a3 * deformVertex->BoneWeight[1]
					+ matrix[2].a3 * deformVertex->BoneWeight[2]
					+ matrix[3].a3 * deformVertex->BoneWeight[3];

				outMatrix.a4 = matrix[0].a4 * deformVertex->BoneWeight[0]
					+ matrix[1].a4 * deformVertex->BoneWeight[1]
					+ matrix[2].a4 * deformVertex->BoneWeight[2]
					+ matrix[3].a4 * deformVertex->BoneWeight[3];


				outMatrix.b1 = matrix[0].b1 * deformVertex->BoneWeight[0]
					+ matrix[1].b1 * deformVertex->BoneWeight[1]
					+ matrix[2].b1 * deformVertex->BoneWeight[2]
					+ matrix[3].b1 * deformVertex->BoneWeight[3];

				outMatrix.b2 = matrix[0].b2 * deformVertex->BoneWeight[0]
					+ matrix[1].b2 * deformVertex->BoneWeight[1]
					+ matrix[2].b2 * deformVertex->BoneWeight[2]
					+ matrix[3].b2 * deformVertex->BoneWeight[3];

				outMatrix.b3 = matrix[0].b3 * deformVertex->BoneWeight[0]
					+ matrix[1].b3 * deformVertex->BoneWeight[1]
					+ matrix[2].b3 * deformVertex->BoneWeight[2]
					+ matrix[3].b3 * deformVertex->BoneWeight[3];

				outMatrix.b4 = matrix[0].b4 * deformVertex->BoneWeight[0]
					+ matrix[1].b4 * deformVertex->BoneWeight[1]
					+ matrix[2].b4 * deformVertex->BoneWeight[2]
					+ matrix[3].b4 * deformVertex->BoneWeight[3];


				outMatrix.c1 = matrix[0].c1 * deformVertex->BoneWeight[0]
					+ matrix[1].c1 * deformVertex->BoneWeight[1]
					+ matrix[2].c1 * deformVertex->BoneWeight[2]
					+ matrix[3].c1 * deformVertex->BoneWeight[3];

				outMatrix.c2 = matrix[0].c2 * deformVertex->BoneWeight[0]
					+ matrix[1].c2 * deformVertex->BoneWeight[1]
					+ matrix[2].c2 * deformVertex->BoneWeight[2]
					+ matrix[3].c2 * deformVertex->BoneWeight[3];

				outMatrix.c3 = matrix[0].c3 * deformVertex->BoneWeight[0]
					+ matrix[1].c3 * deformVertex->BoneWeight[1]
					+ matrix[2].c3 * deformVertex->BoneWeight[2]
					+ matrix[3].c3 * deformVertex->BoneWeight[3];

				outMatrix.c4 = matrix[0].c4 * deformVertex->BoneWeight[0]
					+ matrix[1].c4 * deformVertex->BoneWeight[1]
					+ matrix[2].c4 * deformVertex->BoneWeight[2]
					+ matrix[3].c4 * deformVertex->BoneWeight[3];


				outMatrix.d1 = matrix[0].d1 * deformVertex->BoneWeight[0]
					+ matrix[1].d1 * deformVertex->BoneWeight[1]
					+ matrix[2].d1 * deformVertex->BoneWeight[2]
					+ matrix[3].d1 * deformVertex->BoneWeight[3];

				outMatrix.d2 = matrix[0].d2 * deformVertex->BoneWeight[0]
					+ matrix[1].d2 * deformVertex->BoneWeight[1]
					+ matrix[2].d2 * deformVertex->BoneWeight[2]
					+ matrix[3].d2 * deformVertex->BoneWeight[3];

				outMatrix.d3 = matrix[0].d3 * deformVertex->BoneWeight[0]
					+ matrix[1].d3 * deformVertex->BoneWeight[1]
					+ matrix[2].d3 * deformVertex->BoneWeight[2]
					+ matrix[3].d3 * deformVertex->BoneWeight[3];

				outMatrix.d4 = matrix[0].d4 * deformVertex->BoneWeight[0]
					+ matrix[1].d4 * deformVertex->BoneWeight[1]
					+ matrix[2].d4 * deformVertex->BoneWeight[2]
					+ matrix[3].d4 * deformVertex->BoneWeight[3];
			}

			deformVertex->Position = mesh->mVertices[v];
			deformVertex->Position *= outMatrix;

			//法線変換用に移動成分を削除
			outMatrix.a4 = 0.0f;
			outMatrix.b4 = 0.0f;
			outMatrix.c4 = 0.0f;

			deformVertex->Normal = mesh->mNormals[v];
			deformVertex->Normal *= outMatrix;

			//頂点バッファへ書き込み
			vertex[v].Position.x = deformVertex->Position.x;
			vertex[v].Position.y = deformVertex->Position.y;
			vertex[v].Position.z = deformVertex->Position.z;

			vertex[v].Normal.x = deformVertex->Normal.x;
			vertex[v].Normal.y = deformVertex->Normal.y;
			vertex[v].Normal.z = deformVertex->Normal.z;

			vertex[v].TexCoord.x = mesh->mTextureCoords[0][v].x;
			vertex[v].TexCoord.y = mesh->mTextureCoords[0][v].y;

			vertex[v].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		dx.GetDeviceContext()->Unmap(m_VertexBuffer[m], 0);
	}
}

void AnimationModel::Draw(Wrapper::DirectX11& dx)
{
	
}


void AnimationModel::CreateBone(aiNode* node)
{
	BONE bone;

	m_Bone[node->mName.C_Str()] = bone;

	for (unsigned int n = 0; n < node->mNumChildren; n++)
		CreateBone(node->mChildren[n]);		//再帰呼び出し
}

void AnimationModel::UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix)
{
	BONE* bone = &m_Bone[node->mName.C_Str()];

	//マトリクスの乗算順番に注意
	aiMatrix4x4 worldMatrix;

	worldMatrix = matrix;
	worldMatrix *= bone->AnimationMatrix;

	bone->Matrix = worldMatrix;
	bone->Matrix *= bone->OffsetMatrix;

	//再帰呼び出し
	for (unsigned int n = 0; n < node->mNumChildren; n++)
		UpdateBoneMatrix(node->mChildren[n], worldMatrix);
}
