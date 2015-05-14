//===========================================================
//���X�g�쐬�p�e���v���[�g�֐�
//��ɂ����蔻��p���X�g�̍쐬�Ɣj��
//Creater:Arai Yuhki
//===========================================================
#ifndef _LIST_H_
#define _LIST_H_

template<class T>
class CList
{
public:
	static void LinkHitList(T* This);
	static void UnlinkHitList(T* This);


};
/*�g�p��
class CObject
{
protected:(��������public:)
	static CObject* HitTop;	//�����̐錾���K�{
	static CObject* HitCur;
	CObject* HitNext;
	CObject* HitPrev;
};
	CObject* pObject = new CObject;
	CList<CObject>::LinkList(pObject);

*/

//--------------------------------------------------------
//�����蔻��p���X�g�ɒǉ�
//�^:�����ɓn���ϐ��̃N���X�^
//���� �ǉ��������N���X�I�u�W�F�N�g�̃|�C���^
//--------------------------------------------------------
template<class T>void CList<T>::LinkHitList(T* This)
{
	if(This->HitTop != NULL)//��ڈȍ~�̏���
	{
		T* pObj = This->HitCur;
		pObj->HitNext = This;
		This->HitPrev = pObj;
		This->HitNext = NULL;
		This->HitCur = This;
	}
	else//�ŏ��̈�̎��̏���
	{
		This->HitTop = This;
		This->HitCur = This;
		This->HitPrev = NULL;
		This->HitNext = NULL;
	}
}
//--------------------------------------------------------
//�����蔻��p���X�g����
//�^:�����ɓn���ϐ��̃N���X�^
//���� �폜�������N���X�I�u�W�F�N�g�̃|�C���^
//--------------------------------------------------------
template<class T>void CList<T>::UnlinkHitList(T* This)
{
	if(This==NULL)
	{
		return;
	}
	if(This->HitPrev == NULL)//�擪
	{
		if(This->HitNext != NULL)//��������
		{
			This->HitNext->HitPrev = NULL;
			This->HitTop = This->HitNext;
		}
		else//�Ō�̈������
		{
			This->HitTop = NULL;
			This->HitCur = NULL;
		}
	}
	else if(This->HitNext == NULL)//�I�[
	{
		if(This->HitPrev != NULL)//�O������
		{
			This->HitPrev->HitNext = NULL;
			This->HitCur = This->HitPrev;
		}
		else//�Ō�̈������
		{
			This->HitTop = NULL;
			This->HitCur = NULL;
		}
	}
	else//�O��Ƀf�[�^������Ƃ�
	{
		This->HitPrev->HitNext = This->HitNext;
		This->HitNext->HitPrev = This->HitPrev;
	}

	This->HitPrev = NULL;
	This->HitNext = NULL;

}
#endif