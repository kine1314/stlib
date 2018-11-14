#ifndef	__ST_HASH_H__
#define	__ST_HASH_H__
#include "stlib.h"
#include "st_hash_common.h"


ST_BEGIN_DECLS ;


/*
 * ��ϣ����Ҫ������O(1)ʱ���ڶԲ��Ҷ���λ��������ʵ�ϣ�
 * ������뼯�ϲ�ȷ��������£����ܳ��ִ����ĳ�ͻ����Ȼ��
 * �ܶ�õĹ�ϣ��������������������룬������ͻ���ǲ��ɱ��⣬
 * ���ܳ��������������ԣ���ϣ������������뼯��ȷ��������
 * ��ֻ������ѯ������������£�ѡ����ʵĺ��������ͽ����ͻ
 * �ķ�����perfect hash��������O(1)ʱ������ɲ��Ҷ�����
 * ֧�ֶ�̬�Ĳ���Ͳ��ң���֤������O(height)ʱ�䣬�������
 * ���˹�ϣ������ɵĹ�������̬�ԡ����Ƕ������п��ܳ���
 * worst-case��������������Ѿ�������ʱ�临�Ӷ�ΪO(N)
 * ��ϣ����ϣ������ٶȱȽϿ죬����Ҫ�ıȽ϶���ڴ档���ԱȽ������ڶԲ����ٶ�Ҫ��Ƚϸߡ����ڴ�ռ��㹻��ʱ��
 * ƽ�����������������Ժ��ö��ַ����ҵ�ʱ������ٶȱȽϿ�Ļ��ý���ƽ��������ķ���
 * ��������������ܲ�Ӧ���ù�ϣ����:
	1.�ڴ治��ʱ��
	2.���������ظ�̫����ϣ��ͻ̫��ʱ��
	3.û�к��ʵĹ�ϣ���������ݱ���Ͳ��ܹ�ϣʱ.(��ĳ����ֻ��������ȣ����ڣ�С����������ʱ......������ôȥ��ϣ�أ�������)
 * ѡ������λ�õķ����У�
	�������Ŷ�ַ��
		Hi=(H(key)+di) MOD m i=1,2,...,k(k<=m-1)
		����mΪ����diΪ��������
		���diֵ����Ϊ1,2,3,...m-1��������̽����ɢ�С�
		���diȡֵ����Ϊ1,-1,2,-2,4,-4,9,-9,16,-16,...k*k,-k*k(k<=m/2)
		�ƶ���̽����ɢ�С�
		���diȡֵ����Ϊα������С���α���̽����ɢ�С�
 *
 * */
#define NULLKEY 	0			// 0Ϊ�޼�¼��־


typedef int HashKeyType;// ��ؼ�����Ϊ����

typedef struct
{
	HashKeyType key;
	stint ord;
}HashElemType; // ����Ԫ������

typedef struct
{
	HashElemType *elem; // ����Ԫ�ش洢��ַ����̬��������
	stint count; // ��ǰ����Ԫ�ظ���
	stint sizeindex; // hashsize[sizeindex]Ϊ��ǰ����
}HashTable;



// ����һ���յĹ�ϣ��
stint InitHashTable(HashTable *H) ;
//  ���ٹ�ϣ��H
void DestroyHashTable(HashTable *H);
// �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ��������
// Ԫ���ڱ���λ��,������SUCCESS;����,��pָʾ����λ��,������UNSUCCESS
// c���ԼƳ�ͻ���������ֵ���㣬���������ʱ�ο���
stint SearchHash(HashTable H, HashKeyType K, stint *p, stint *c);
// ���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������1��
// ����ͻ�����������ؽ���ϣ��
int InsertHash(HashTable *,HashElemType); // �Ժ���������
// �ؽ���ϣ��
void RecreateHashTable(HashTable *H);
// ����ϣ��ַ��˳�������ϣ��
void TraverseHash(HashTable H,void(*Vi)(stint,HashElemType));
// �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ��������
// Ԫ���ڱ���λ��,������SUCCESS;����,����UNSUCCESS
stint Find(HashTable H,HashKeyType K,stint *p);

ST_END_DECLS ;
#endif	/* __ST_HASH_H__ */
