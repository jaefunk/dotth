#include "D3D11Camera.h"


D3D11Camera::D3D11Camera()
{
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);;
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

D3D11Camera::~D3D11Camera()
{
}


void D3D11Camera::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void D3D11Camera::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void D3D11Camera::Render()
{
	XMFLOAT3 up, position, lookAt;

	// 위쪽을 가리키는 벡터를 설정합니다.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// XMVECTOR 구조체에 로드한다.
	XMVECTOR upVector = XMLoadFloat3(&up);

	// 3D월드에서 카메라의 위치를 ​​설정합니다.
	position = m_position;

	// XMVECTOR 구조체에 로드한다.
	XMVECTOR positionVector = XMLoadFloat3(&position);

	// Calculate the rotation in radians.
	float radians = m_rotation.y * 0.0174532925f;

	// 기본적으로 카메라가 찾고있는 위치를 설정합니다.
	lookAt.x = sinf(radians) + m_position.x;
	lookAt.y = m_position.y;
	lookAt.z = cosf(radians) + m_position.z;

	// XMVECTOR 구조체에 로드한다.
	XMVECTOR lookAtVector = XMLoadFloat3(&lookAt);

	// 마지막으로 세 개의 업데이트 된 벡터에서 뷰 행렬을 만듭니다.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}


void D3D11Camera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}