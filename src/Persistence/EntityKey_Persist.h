/*
 * Common_Persist.h
 *
 *  Created on: 2015年5月4日
 *      Author: Administrator
 */

#ifndef COMMON_PERSIST_H_
#define COMMON_PERSIST_H_


/*根据传入的实体名entName及实体个数count，为这个count个新实体分配一个长度为count的主键值区间，
 * 使得每个新实体在该区间内都可以分配到 唯一的 主键。返回值为该主键区间的最小值*/
long EntKey_Perst_GetNewKeys(const char entName[], int count);

#endif /* COMMON_PERSIST_H_ */
