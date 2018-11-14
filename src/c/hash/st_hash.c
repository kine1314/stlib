#include <stdlib.h>
#include <stdio.h>
#include "st_hash.h"




// ���Ŷ�ַ��ϣ���Ĵ洢�ṹ
static stint hashsize[]={11,19,29,37}; // ��ϣ��������������һ�����ʵ���������
static stint m=0; // ��ϣ��������ȫ�ֱ���


// ����һ���յĹ�ϣ��
stint InitHashTable(HashTable *H)
{
    int i;
    (*H).count=0; 						// ��ǰԪ�ظ���Ϊ0
    (*H).sizeindex=0; 					// ��ʼ�洢����Ϊhashsize[0]
    m=hashsize[0];
    (*H).elem=(HashElemType*)malloc(m*sizeof(HashElemType));
    if(!(*H).elem)
        exit(0); 						// �洢����ʧ��
    for(i=0;i<m;i++)
        (*H).elem[i].key=NULLKEY; 		// δ���¼�ı�־

    return 1;
}

//  ���ٹ�ϣ��H
void DestroyHashTable(HashTable *H)
{
    free((*H).elem);
    (*H).elem=NULL;
    (*H).count=0;
    (*H).sizeindex=0;
}

// һ���򵥵Ĺ�ϣ����(mΪ������ȫ�ֱ���)
static unsigned int Hash(HashKeyType K)
{
    return K%m;
}

// ���Ŷ�ַ��������ͻ
// Hi = ( H(key) + di ) MOD m i=1, 2, ��,s
void collision(int *p,int d) // ����̽����ɢ��
{
    *p=(*p+d)%m;
}

stint SearchHash(HashTable H,HashKeyType K,int *p,int *c)
{
    *p=Hash(K); 					// ��ù�ϣ��ַ
    while((H.elem[*p].key!=NULLKEY) && (!(K == H.elem[*p].key)))
    {
        // ��λ�������м�¼�����ҹؼ��ֲ����
        (*c)++;
        if(*c<m)
            collision(p,*c); 		// �����һ̽���ַp
        else
            break;
    }
    //���ҳɹ���p���ش�������Ԫ��λ��
    if (K == H.elem[*p].key)
    	return SUCCESS ;
    else
    {
        return UNSUCCESS ;				// ���Ҳ��ɹ�(H.elem[p].key==NULLKEY)��p���ص��ǲ���λ��
    }
}

void RecreateHashTable(HashTable *H) // �ؽ���ϣ��
{
    stint i,count=(*H).count;
    HashElemType *p,*elem=(HashElemType*)malloc(count*sizeof(HashElemType));
    p=elem;
    printf("�ؽ���ϣ��\n");
    for(i=0;i<m;i++) 						// ����ԭ�е����ݵ�elem��
        if(((*H).elem+i)->key!=NULLKEY) 	// �õ�Ԫ������
            *p++=*((*H).elem+i);
    (*H).count=0;
    (*H).sizeindex++; 						// ����洢����
    m=hashsize[(*H).sizeindex];
    p=(HashElemType*)realloc((*H).elem,m*sizeof(HashElemType));
    if(!p)
        exit(0); 							// �洢����ʧ��
    (*H).elem=p;
    for(i=0;i<m;i++)
        (*H).elem[i].key=NULLKEY; 			// δ���¼�ı�־(��ʼ��)
    for(p=elem;p<elem+count;p++) 			// ��ԭ�е����ݰ����µı������뵽�ؽ��Ĺ�ϣ����
        InsertHash(H,*p);
}

// ���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������1��
// ����ͻ�����������ؽ���ϣ����
stint InsertHash(HashTable *H,HashElemType e)
{
    stint c,p;
    c=0;

    if(SearchHash(*H,e.key,&p,&c))			// ����������e����ͬ�ؼ��ֵ�Ԫ��
    {
    	return DUPLICATE ;
    }
    else if(c<hashsize[(*H).sizeindex]/2)	// ��ͻ����cδ�ﵽ����,(c�ķ�ֵ�ɵ�)
    {
        // ����e
        (*H).elem[p]=e;
        ++(*H).count;
        return 1;
    }
    else
    {
        RecreateHashTable(H); // �ؽ���ϣ��
    }

    return 0;
}

// ����ϣ��ַ��˳�������ϣ��
void TraverseHash(HashTable H,void(*Vi)(stint,HashElemType))
{
	stint i;
	printf("��ϣ��ַ0��%d\n",m-1);
	for(i=0;i<m;i++)
		if(H.elem[i].key!=NULLKEY) // ������
			Vi(i,H.elem[i]);
}

// �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ��������
// Ԫ���ڱ���λ��,������SUCCESS;����,����UNSUCCESS
stint Find(HashTable H,HashKeyType K,stint *p)
{
	stint c=0;
	*p=Hash(K); 					// ��ù�ϣ��ַ
	while(H.elem[*p].key!=NULLKEY&&!(K == H.elem[*p].key))
	{ 								// ��λ�������м�¼�����ҹؼ��ֲ����
		c++;
		if(c<m)
			collision(p,c); 		// �����һ̽���ַp
		else
			return UNSUCCESS; 		// ���Ҳ��ɹ�(H.elem[p].key==NULLKEY)
	}
	if (K == H.elem[*p].key)
		return SUCCESS; 			// ���ҳɹ���p���ش�������Ԫ��λ��
	else
		return UNSUCCESS; 			// ���Ҳ��ɹ�(H.elem[p].key==NULLKEY)
}


