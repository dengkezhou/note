#ifndef VNEC_LOCALCASE_JOINT_TEST_H
#define VNEC_LOCALCASE_JOINT_TEST_H


struct venc_join_test_param {
	int id;
	char case_name[5];
};

/*初始化，成功返回0，失败返回-1*/
int venc_joint_test_init(void * param);

/*开始编码， count需要从0开始递增，总是返回0*/
int venc_joint_test_start(int id, int count);

/*返回 1-表示编码完成， 0-表示编码未完成*/
int venc_joint_test_get_status(int id);
#endif