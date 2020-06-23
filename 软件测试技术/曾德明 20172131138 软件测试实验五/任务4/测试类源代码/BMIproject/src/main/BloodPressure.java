package main;

import java.util.Scanner;

/**
 * 血压类
 */
public class BloodPressure {
    // 定义属性
    int systolicPressure;   // 收缩压
    int diatolicPressure;   // 舒张压

    // getter & setter
    public int getSystolicPressure() {
        return systolicPressure;
    }

    public void setSystolicPressure(int systolicPressure) {
        this.systolicPressure = systolicPressure;
    }

    public int getDiatolicPressure() {
        return diatolicPressure;
    }

    public void setDiatolicPressure(int diatolicPressure) {
        this.diatolicPressure = diatolicPressure;
    }

    // 一次性改变参数
    public void setParam(int systolicPressure, int diatolicPressure) {
        this.systolicPressure = systolicPressure;
        this.diatolicPressure = diatolicPressure;
    }

    // 构造函数
    public BloodPressure() {
        this.systolicPressure = 0;
        this.diatolicPressure = 0;
    }

    public BloodPressure(int systolicPressure, int diatolicPressure) {
        this.systolicPressure = systolicPressure;
        this.diatolicPressure = diatolicPressure;
    }

    // 根据血压值判断所属血压分级
    public String getPressureLevel() {
        String result = "";

        if(systolicPressure >= 180 || diatolicPressure >= 110) {
            result = "3级高血压";
        }
        else if (systolicPressure >= 160 || diatolicPressure >= 100) {
            result = "2级高血压";
        }
        else if (systolicPressure >= 140 || diatolicPressure >= 90) {
            result = "1级高血压";
        }
        else if (systolicPressure >= 120 && diatolicPressure >= 80) {
            result = "正常高值";
        }
        else if (systolicPressure < 120 && diatolicPressure < 80){
            result = "正常";
        }
        else {
            result = "不满足任意一种分级标准,请重新测量!";
        }

        return result;
    }

    /*
    public static void main(String[] args) {
        // 方案1：通过main函数由用户直接输入测试
        // 1.输入身高体重
        Scanner scan = new Scanner(System.in);
        System.out.println("please input systolicPressure and diatolicPressure:");
        int systolicPressure = scan.nextInt();   // 收缩压
        int diatolicPressure = scan.nextInt();   // 舒张压
        // 2.新建一个测试类BMI(weight,height)
        BloodPressure test = new BloodPressure(systolicPressure, diatolicPressure);
        // 3.调用被测方法
        String result = test.getPressureLevel();
        // 4.校验结果
        System.out.println(result);
    }
     */
}
