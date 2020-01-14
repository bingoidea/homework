/*
Navicat MySQL Data Transfer

Source Server         : MySQL
Source Server Version : 50724
Source Host           : localhost:3306
Source Database       : test

Target Server Type    : MYSQL
Target Server Version : 50724
File Encoding         : 65001

Date: 2020-01-14 17:16:54
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for travel_information
-- ----------------------------
DROP TABLE IF EXISTS `travel_information`;
CREATE TABLE `travel_information` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '每条记录的id',
  `gender` varchar(255) DEFAULT '' COMMENT '性别：男，女',
  `age` int(11) DEFAULT NULL,
  `gz_state` varchar(11) DEFAULT '' COMMENT '广州的区（1越秀， 2海珠，3天河，4番禺，5花都，6从化，7黄埔）',
  `job` varchar(255) DEFAULT '',
  `way_to_travel` varchar(255) DEFAULT '',
  `cause` varchar(255) DEFAULT '',
  `didi_stage` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of travel_information
-- ----------------------------
INSERT INTO `travel_information` VALUES ('1', '男', '21', '越秀区', '学生', '步行', '消费低', '1');
INSERT INTO `travel_information` VALUES ('2', '女', '31', '越秀区', '老师', '私家车', '高效便捷', '2');
INSERT INTO `travel_information` VALUES ('3', '男', '42', '越秀区', '企业职工', '公交车', '长期习惯', '3');
INSERT INTO `travel_information` VALUES ('4', '女', '53', '越秀区', '经理', '地铁', '高效便捷', '4');
INSERT INTO `travel_information` VALUES ('5', '女', '41', '越秀区', '公务员', '自行车', '舒适', '5');
INSERT INTO `travel_information` VALUES ('6', '男', '31', '天河区', '老师', '滴滴叫车', '高效便捷', '1');
INSERT INTO `travel_information` VALUES ('7', '男', '12', '天河区', '学生', '自行车', '消费低', '2');
INSERT INTO `travel_information` VALUES ('8', '女', '23', '天河区', '企业职工', '步行', '长期习惯', '3');
INSERT INTO `travel_information` VALUES ('9', '女', '34', '天河区', '公务员', '私家车', '舒适', '4');
INSERT INTO `travel_information` VALUES ('10', '男', '64', '越秀区', '退休', '公交车', '消费低', '5');
INSERT INTO `travel_information` VALUES ('11', '男', '14', '白云区', '学生', '地铁', '长期习惯', '1');
INSERT INTO `travel_information` VALUES ('12', '男', '23', '白云区', '学生', '滴滴叫车', '高效便捷', '2');
INSERT INTO `travel_information` VALUES ('13', '男', '34', '海珠区', '公务员', '私家车', '舒适', '3');
INSERT INTO `travel_information` VALUES ('14', '男', '45', '海珠区', '老师', '私家车', '长期习惯', '4');
INSERT INTO `travel_information` VALUES ('15', '女', '23', '从化区', '企业职工', '地铁', '消费低', '5');
INSERT INTO `travel_information` VALUES ('16', '男', '45', '从化区', '老师', '公交车', '舒适', '1');
INSERT INTO `travel_information` VALUES ('17', '女', '15', '从化区', '学生', '自行车', '高效便捷', '2');
INSERT INTO `travel_information` VALUES ('18', '男', '41', '番禺区', '经理', '步行', '舒适', '3');
INSERT INTO `travel_information` VALUES ('19', '女', '42', '番禺区', '经理', '滴滴叫车', '长期习惯', '4');
INSERT INTO `travel_information` VALUES ('20', '女', '43', '海珠区', '公务员', '滴滴叫车', '高效便捷', '5');
INSERT INTO `travel_information` VALUES ('21', '女', '55', '海珠区', '经理', '地铁', '消费低', '1');
INSERT INTO `travel_information` VALUES ('22', '女', '51', '白云区', '企业职工', '自行车', '消费低', '2');
INSERT INTO `travel_information` VALUES ('23', '女', '52', '白云区', '企业职工', '公交车', '长期习惯', '3');
INSERT INTO `travel_information` VALUES ('24', '男', '53', '从化区', '经理', '私家车', '高效便捷', '4');
INSERT INTO `travel_information` VALUES ('25', '女', '67', '从化区', '退休', '步行', '舒适', '5');
INSERT INTO `travel_information` VALUES ('26', '女', '68', '越秀区', '退休', '私家车', '长期习惯', '1');
INSERT INTO `travel_information` VALUES ('27', '女', '69', '越秀区', '退休', '地铁', '舒适', '2');
INSERT INTO `travel_information` VALUES ('28', '男', '35', '花都区', '老师', '自行车', '高效便捷', '3');
INSERT INTO `travel_information` VALUES ('29', '男', '36', '花都区', '老师', '公交车', '消费低', '4');
INSERT INTO `travel_information` VALUES ('30', '男', '37', '花都区', '工人', '步行', '高效便捷', '5');
INSERT INTO `travel_information` VALUES ('31', '男', '25', '花都区', '工人', '滴滴叫车', '舒适', '1');
INSERT INTO `travel_information` VALUES ('32', '男', '62', '花都区', '退休', '自行车', '消费低', '2');
INSERT INTO `travel_information` VALUES ('33', '女', '27', '花都区', '企业职工', '步行', '长期习惯', '3');
INSERT INTO `travel_information` VALUES ('34', '女', '28', '越秀区', '企业职工', '私家车', '消费低', '4');
INSERT INTO `travel_information` VALUES ('35', '男', '21', '从化区', '学生', '地铁', '高效便捷', '5');
INSERT INTO `travel_information` VALUES ('36', '女', '41', '白云区', '经理', '滴滴叫车', '舒适', '5');
INSERT INTO `travel_information` VALUES ('37', '女', '42', '海珠区', '经理', '公交车', '长期习惯', '2');
INSERT INTO `travel_information` VALUES ('38', '女', '53', '番禺区', '经理', '自行车', '消费低', '3');
INSERT INTO `travel_information` VALUES ('39', '男', '57', '花都区', '老师', '滴滴叫车', '高效便捷', '4');
INSERT INTO `travel_information` VALUES ('40', '女', '58', '越秀区', '公务员', '步行', '长期习惯', '5');
INSERT INTO `travel_information` VALUES ('41', '男', '69', '越秀区', '退休', '公交车', '舒适', '1');
INSERT INTO `travel_information` VALUES ('42', '女', '64', '海珠区', '退休', '地铁', '消费低', '2');
INSERT INTO `travel_information` VALUES ('43', '女', '53', '海珠区', '公务员', '私家车', '高效便捷', '3');
INSERT INTO `travel_information` VALUES ('44', '女', '43', '花都区', '公务员', '自行车', '长期习惯', '4');
INSERT INTO `travel_information` VALUES ('45', '男', '23', '花都区', '学生', '公交车', '舒适', '5');
INSERT INTO `travel_information` VALUES ('46', '女', '34', '从化区', '企业职工', '步行', '高效便捷', '1');
INSERT INTO `travel_information` VALUES ('47', '男', '36', '从化区', '企业职工', '地铁', '长期习惯', '2');
INSERT INTO `travel_information` VALUES ('48', '女', '22', '白云区', '学生', '滴滴叫车', '消费低', '3');
INSERT INTO `travel_information` VALUES ('49', '女', '44', '白云区', '老师', '步行', '舒适', '4');
INSERT INTO `travel_information` VALUES ('50', '男', '33', '番禺区', '老师', '私家车', '消费低', '5');
INSERT INTO `travel_information` VALUES ('51', '女', '56', '越秀区', '老师', '滴滴叫车', '高效便捷', '5');
INSERT INTO `travel_information` VALUES ('52', '男', '24', '越秀区', '学生', '公交车', '消费低', '4');
INSERT INTO `travel_information` VALUES ('53', '男', '18', '天河区', '学生', '公交车', '消费低', '4');
INSERT INTO `travel_information` VALUES ('54', '女', '42', '天河区', '公务员', '地铁', '长期习惯', '3');
INSERT INTO `travel_information` VALUES ('55', '男', '13', '白云区', '学生', '私家车', '长期习惯', '1');
INSERT INTO `travel_information` VALUES ('56', '女', '24', '海珠区', '学生', '步行', '长期习惯', '2');
INSERT INTO `travel_information` VALUES ('57', '男', '35', '海珠区', '公务员', '自行车', '消费低', '3');
INSERT INTO `travel_information` VALUES ('58', '女', '46', '从化区', '经理', '滴滴叫车', '高效便捷', '4');
INSERT INTO `travel_information` VALUES ('59', '男', '57', '从化区', '经理', '滴滴叫车', '舒适', '5');
INSERT INTO `travel_information` VALUES ('60', '女', '68', '从化区', '退休', '滴滴叫车', '舒适', '4');
INSERT INTO `travel_information` VALUES ('61', '男', '70', '番禺区', '退休', '公交车', '消费低', '3');
INSERT INTO `travel_information` VALUES ('62', '女', '25', '番禺区', '企业职工', '地铁', '长期习惯', '2');
INSERT INTO `travel_information` VALUES ('63', '男', '13', '番禺区', '学生', '地铁', '高效便捷', '1');
INSERT INTO `travel_information` VALUES ('64', '女', '35', '番禺区', '企业职工', '地铁', '消费低', '2');
INSERT INTO `travel_information` VALUES ('65', '男', '57', '花都区', '经理', '私家车', '舒适', '3');
INSERT INTO `travel_information` VALUES ('66', '女', '45', '花都区', '教师', '地铁', '舒适', '4');
