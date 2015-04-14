#ifndef _MATH_TABLE_H_
#define _MATH_TABLE_H_

#include <stdio.h>
#include <math.h>

// �p�x�̐��K��(PI�`-PI)
#define REVISE_PI(radian) {if((radian) > PI){(radian) -= (2.0f * PI);}\
		else if((radian) < -PI){(radian) += (2.0f * PI);}}


// �p�֘A
#define PI     (3.141592654f) // �~����
#define RAD_TO_DEG   (57.29577951f) // 1���W�A�����x
#define DEG_TO_RAD   (0.017453293f) // 1�x�����W�A��

// �x�����W�A��
#define DEG2RAD(degree)  ((degree) * DEG_TO_RAD)
// ���W�A�����x
#define RAD2DEG(radian)  ((radian) * RAD_TO_DEG)

class CMath
{
private:
	float _tsin[360];//�T�C���e�[�u��
	float _tcos[360];//�R�T�C���e�[�u��
	float _ttan[360];//�^���W�F���g�e�[�u��
	float _tatan[513];

	//�œK���֐�
	int Optimize(int deg);
	int RadOptimize(float rad);

	CMath(const CMath &src);

public:

	CMath();//�R���X�g���N�^


	//�e�[�u������̎擾
	//�f�B�O���[
	float tSin_deg(int deg);
	float tCos_deg(int deg);
	float tTan_deg(int deg);
	//���W�A��
	float tSin_rad(float rad);
	float tCos_rad(float rad);
	float tTan_rad(float rad);
	float tAtan2(float index){ return _tatan[(int)(index)]; }

};

//������(PI/180)�������Ă���ꍇ�͂�����
float Sin_Rad(float rad);
float Cos_Rad(float rad);
float Tan_Rad(float rad);

//������30����45���̂悤�Ȑ����Ȃ炱����
float Sin_Deg(int deg);
float Cos_Deg(int deg);
float Tan_Deg(int deg);
float Atan2(float y,float x);
float t_sqrtF(const float& x);

#endif