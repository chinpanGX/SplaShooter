/*-----------------------------------------------

	[Mesh.cpp]
	Author : 出合翔太

------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "Model.h"

// モデルの読み込み
void StaticMesh::Model::LoadObject(const char * FileName, Mesh * Mesh)
{
	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir); // パスからファイル名を取り除く

	D3DXVECTOR3	*positionArray;
	D3DXVECTOR3	*normalArray;
	D3DXVECTOR2	*texcoordArray;

	unsigned __int32	positionNum = 0;
	unsigned __int32	normalNum = 0;
	unsigned __int32	texcoordNum = 0;
	unsigned __int32	vertexNum = 0;
	unsigned __int32	indexNum = 0;
	unsigned __int32	in = 0;
	unsigned __int32	subsetNum = 0;

	Material	*materialArray = NULL;
	unsigned __int32	materialNum = 0;

	char str[256];
	char *s;
	char c;

	FILE *file;
	file = fopen(FileName, "rt");
	assert(file);

	//要素数カウント
	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}
		// 文字列の比較して一致するかどうか
		if (strcmp(str, "v") == 0)
		{
			positionNum++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			normalNum++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			texcoordNum++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			subsetNum++;
		}
		else if (strcmp(str, "f") == 0)
		{
			in = 0;
			do
			{
				fscanf(file, "%s", str);
				vertexNum++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//四角は三角に分割
			if (in == 4)
				in = 6;

			indexNum += in;
		}
	}


	//メモリ確保
	positionArray = new D3DXVECTOR3[positionNum];
	normalArray = new D3DXVECTOR3[normalNum];
	texcoordArray = new D3DXVECTOR2[texcoordNum];
	Mesh->m_VertexArray = new Wrapper::VERTEX_3D[vertexNum];
	Mesh->m_VertexNum = vertexNum;
	Mesh->m_IndexArray = new unsigned __int32[indexNum];
	Mesh->m_IndexNum = indexNum;
	Mesh->m_SubsetArray = new Subset[subsetNum];
	Mesh->m_SubsetNum = subsetNum;

	//要素読込
	D3DXVECTOR3 *position = positionArray;
	D3DXVECTOR3 *normal = normalArray;
	D3DXVECTOR2 *texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;

	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "mtllib") == 0)
		{
			//マテリアルファイル
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//オブジェクト名
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//頂点座標
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//法線
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//テクスチャ座標
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//マテリアル
			fscanf(file, "%s", str);

			if (sc != 0)
			{
				Mesh->m_SubsetArray[sc - 1].m_IndexNum = ic - Mesh->m_SubsetArray[sc - 1].m_StartIndex;
			}

			Mesh->m_SubsetArray[sc].m_StartIndex = ic;


			for (unsigned int i = 0; i < materialNum; i++)
			{
				if (strcmp(str, materialArray[i].m_Name) == 0)
				{
					Mesh->m_SubsetArray[sc].m_Material.m_Material = materialArray[i].m_Material;
					strcpy(Mesh->m_SubsetArray[sc].m_Material.m_TextureName, materialArray[i].m_TextureName);
					strcpy(Mesh->m_SubsetArray[sc].m_Material.m_Name, materialArray[i].m_Name);

					break;
				}
			}

			sc++;

		}
		else if (strcmp(str, "f") == 0)
		{
			//面
			in = 0;
			do
			{
				fscanf(file, "%s", str);
				s = strtok(str, "/");
				Mesh->m_VertexArray[vc].Position = positionArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					//テクスチャ座標が存在しない場合もある
					s = strtok(NULL, "/");
					Mesh->m_VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1];
				}
				s = strtok(NULL, "/");
				Mesh->m_VertexArray[vc].Normal = normalArray[atoi(s) - 1];
				Mesh->m_VertexArray[vc].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				Mesh->m_IndexArray[ic] = vc;
				ic++;
				vc++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//四角は三角に分割
			if (in == 4)
			{
				Mesh->m_IndexArray[ic] = vc - 4;
				ic++;
				Mesh->m_IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}
	if (sc != 0)
	{
		Mesh->m_SubsetArray[sc - 1].m_IndexNum = ic - Mesh->m_SubsetArray[sc - 1].m_StartIndex;
	}
	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}

void StaticMesh::Model::LoadMaterial(const char * FileName, Material ** MaterialArray, unsigned __int32* MaterialNum)
{
	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir);
	char str[256];
	FILE *file;
	file = fopen(FileName, "rt");
	assert(file);

	Material *materialArray;
	unsigned int materialNum = 0;

	//要素数カウント
	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
		{
			break;
		}
		if (strcmp(str, "newmtl") == 0)
		{
			materialNum++;
		}
	}
	//メモリ確保
	materialArray = new Material[materialNum];
	//要素読込
	int mc = -1;
	fseek(file, 0, SEEK_SET);
	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}
		if (strcmp(str, "newmtl") == 0)
		{
			//マテリアル名
			mc++;
			fscanf(file, "%s", materialArray[mc].m_Name);
			strcpy(materialArray[mc].m_TextureName, "");
			materialArray[mc].m_Material.Emission.r = 0.0f;
			materialArray[mc].m_Material.Emission.g = 0.0f;
			materialArray[mc].m_Material.Emission.b = 0.0f;
			materialArray[mc].m_Material.Emission.a = 0.0f;
		}
		else if (strcmp(str, "Ka") == 0)
		{
			//アンビエント
			fscanf(file, "%f", &materialArray[mc].m_Material.Ambient.r);
			fscanf(file, "%f", &materialArray[mc].m_Material.Ambient.g);
			fscanf(file, "%f", &materialArray[mc].m_Material.Ambient.b);
			materialArray[mc].m_Material.Ambient.a = 1.0f;
		}
		else if (strcmp(str, "Kd") == 0)
		{
			//ディフューズ
			fscanf(file, "%f", &materialArray[mc].m_Material.Diffuse.r);
			fscanf(file, "%f", &materialArray[mc].m_Material.Diffuse.g);
			fscanf(file, "%f", &materialArray[mc].m_Material.Diffuse.b);
			materialArray[mc].m_Material.Diffuse.a = 1.0f;
		}
		else if (strcmp(str, "Ks") == 0)
		{
			//スペキュラ
			fscanf(file, "%f", &materialArray[mc].m_Material.Specular.r);
			fscanf(file, "%f", &materialArray[mc].m_Material.Specular.g);
			fscanf(file, "%f", &materialArray[mc].m_Material.Specular.b);
			materialArray[mc].m_Material.Specular.a = 1.0f;
		}
		else if (strcmp(str, "Ns") == 0)
		{
			//スペキュラ強度
			fscanf(file, "%f", &materialArray[mc].m_Material.Shininess);
		}
		else if (strcmp(str, "d") == 0)
		{
			//アルファ
			fscanf(file, "%f", &materialArray[mc].m_Material.Diffuse.a);
		}
		else if (strcmp(str, "map_Kd") == 0)
		{
			//テクスチャ
			fscanf(file, "%s", str);
			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);
			strcat(materialArray[mc].m_TextureName, path);
		}
	}
	*MaterialArray = materialArray;
	*MaterialNum = materialNum;
}

// ロード
void StaticMesh::Model::Load(const char * FileName)
{
	Mesh mesh;
	LoadObject(FileName, &mesh);
	// 頂点バッファ生成
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof(Wrapper::VERTEX_3D) * mesh.m_VertexNum;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vsd;
	ZeroMemory(&vsd, sizeof(vsd));
	vsd.pSysMem = mesh.m_VertexArray;
	m_dx.GetDevice()->CreateBuffer(&vbd, &vsd, &m_VertexBuffer);

	// インデックスバッファ生成
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(unsigned __int32) * mesh.m_IndexNum;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA isd;
	ZeroMemory(&isd, sizeof(isd));
	isd.pSysMem = mesh.m_IndexArray;
	m_dx.GetDevice()->CreateBuffer(&ibd, &isd, &m_IndexBuffer);


	// サブセット設定
	m_SubsetArray = new Subset[mesh.m_SubsetNum];
	m_SubsetNum = mesh.m_SubsetNum;
	unsigned __int32 CountSubset = 0;
	for (CountSubset; CountSubset < mesh.m_SubsetNum; CountSubset++)
	{
		m_SubsetArray[CountSubset].m_StartIndex = mesh.m_SubsetArray[CountSubset].m_StartIndex;
		m_SubsetArray[CountSubset].m_IndexNum = mesh.m_SubsetArray[CountSubset].m_IndexNum;
		m_SubsetArray[CountSubset].m_Material.m_Material = mesh.m_SubsetArray[CountSubset].m_Material.m_Material;
		m_SubsetArray[CountSubset].m_Material.m_Texture = NULL;
		D3DX11CreateShaderResourceViewFromFile(m_dx.GetDevice(), mesh.m_SubsetArray[CountSubset].m_Material.m_TextureName, NULL, NULL, &m_SubsetArray[i].m_Material.m_Texture, NULL);
		assert(m_SubsetArray[i].m_Material.m_Texture);
	}
	delete[] mesh.m_VertexArray;
	delete[] mesh.m_IndexArray;
	delete[] mesh.m_SubsetArray;
}

// アンロード
void StaticMesh::Model::Unload()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	unsigned __int32 i = 0;
	for (i; i < m_SubsetNum; i++)
	{
		m_SubsetArray[i].m_Material.m_Texture->Release();
	}
	delete[] m_SubsetArray;
}

// 描画
void StaticMesh::Model::Draw()
{
	// 頂点バッファの設定
	UINT stride = sizeof(Wrapper::VERTEX_3D);
	UINT offset = 0;
	m_dx.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// インデックスバッファの設定
	m_dx.GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// プリミティブポロジ設定
	m_dx.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	unsigned __int32 CountSubset = 0;
	for (CountSubset; CountSubset < m_SubsetNum; CountSubset++)
	{
		// マテリアルの設定
		m_dx.SetMaterial(m_SubsetArray[CountSubset].m_Material.m_Material);
		// テクスチャの設定
		m_dx.GetDeviceContext()->PSSetShaderResources(0, 1, &m_SubsetArray[CountSubset].m_Material.m_Texture);
		// ポリゴン描画
		m_dx.GetDeviceContext()->DrawIndexed(m_SubsetArray[CountSubset].m_IndexNum, m_SubsetArray[CountSubset].m_StartIndex, 0);
	}
}
