#pragma once

// #define NULL 0
enum NODE_TYPE { INTERNAL, LEAF };        // ������ͣ��ڽ�㡢Ҷ�ӽ��
enum SIBLING_DIRECTION { LEFT, RIGHT };   // �ֵܽ�㷽�����ֵܽ�㡢���ֵܽ��
typedef int KeyType;                 // ������
typedef int DataType;                  // ֵ����
const int ORDER = 7;                   // B+���Ľף��Ǹ��ڽ�����С����������
const int MINNUM_KEY = ORDER - 1;        // ��С��ֵ����
const int MAXNUM_KEY = 2 * ORDER - 1;      // ����ֵ����
const int MINNUM_CHILD = MINNUM_KEY + 1; // ��С��������
const int MAXNUM_CHILD = MAXNUM_KEY + 1; // �����������
const int MINNUM_LEAF = MINNUM_KEY;    // ��СҶ�ӽ���ֵ����
const int MAXNUM_LEAF = MAXNUM_KEY;    // ���Ҷ�ӽ���ֵ����

// ������
class CNode {
public:
	CNode();
	virtual ~CNode();

	NODE_TYPE getType() const { return m_Type; }
	void setType(NODE_TYPE type) { m_Type = type; }
	int getKeyNum() const { return m_KeyNum; }
	void setKeyNum(int n) { m_KeyNum = n; }
	KeyType getKeyValue(int i) const { return m_KeyValues[i]; }
	void setKeyValue(int i, KeyType key) { m_KeyValues[i] = key; }
	int getKeyIndex(KeyType key)const;  // �ҵ���ֵ�ڽ���д洢���±�
	// ���麯��������ӿ�
	virtual void removeKey(int keyIndex, int childIndex) = 0;  // �ӽ�����Ƴ���ֵ
	virtual void split(CNode* parentNode, int childIndex) = 0; // ���ѽ��
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex) = 0;  // �ϲ����
	virtual void clear() = 0; // ��ս�㣬ͬʱ����ս�����������������
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d) = 0; // ���ֵܽ���н�һ����ֵ
	virtual int getChildIndex(KeyType key, int keyIndex)const = 0;  // ���ݼ�ֵ��ȡ���ӽ��ָ���±�
protected:
	NODE_TYPE m_Type;
	int m_KeyNum;
	KeyType m_KeyValues[MAXNUM_KEY];
};

// �ڽ��
class CInternalNode : public CNode {
public:
	CInternalNode();
	virtual ~CInternalNode();

	CNode* getChild(int i) const { return m_Childs[i]; }
	void setChild(int i, CNode* child) { m_Childs[i] = child; }
	void insert(int keyIndex, int childIndex, KeyType key, CNode* childNode);
	virtual void split(CNode* parentNode, int childIndex);
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex);
	virtual void removeKey(int keyIndex, int childIndex);
	virtual void clear();
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d);
	virtual int getChildIndex(KeyType key, int keyIndex)const;
private:
	CNode* m_Childs[MAXNUM_CHILD];
};

// Ҷ�ӽ��
class CLeafNode : public CNode {
public:
	CLeafNode();
	virtual ~CLeafNode();

	CLeafNode* getLeftSibling() const { return m_LeftSibling; }
	void setLeftSibling(CLeafNode* node) { m_LeftSibling = node; }
	CLeafNode* getRightSibling() const { return m_RightSibling; }
	void setRightSibling(CLeafNode* node) { m_RightSibling = node; }
	DataType getData(int i) const { return m_Datas[i]; }
	void setData(int i, const DataType& data) { m_Datas[i] = data; }
	void insert(KeyType key, const DataType& data);
	virtual void split(CNode* parentNode, int childIndex);
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex);
	virtual void removeKey(int keyIndex, int childIndex);
	virtual void clear();
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d);
	virtual int getChildIndex(KeyType key, int keyIndex)const;
private:
	CLeafNode* m_LeftSibling;
	CLeafNode* m_RightSibling;
	DataType m_Datas[MAXNUM_LEAF];
};
