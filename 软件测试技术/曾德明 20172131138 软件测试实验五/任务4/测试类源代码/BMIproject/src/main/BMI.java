package main;

import java.util.Scanner;

/**
 * BMI类
 */
public class BMI {
    // 定义属性
    private double weight; // 体重
    private double height; // 身高

    // get & set
    public double getWeight() {
        return weight;
    }

    public double getHeight() {
        return height;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    // 一次性设置变量
    public void serParams(double weight, double height) {
        this.weight = weight;
        this.height = height;
    }

    // 定义构造函数
    public BMI() {
        this.weight = 1.0;
        this.height = 1.0;
    }

    public BMI(double weight, double height) {
        this.weight = weight;
        this.height = height;
    }

    // 定义功能方法：计算BMI
    public String getBMIType() {
        String result = "";

        // 输入为正数
        if (this.height <= 0 || this.weight <= 0) {
            return result = "输入错误!";
        }
        // 以米为单位，身高不可能超过3米，因此可设定如果身高大于3，则用户输入的是厘米值
        if (this.height > 3) {
            return result = "输入身高单位应为米!";
        }

        double bmi = this.weight / (this.height * this.height);

        if(bmi >= 28) {
            result = "肥胖";
        }
        else if (bmi >= 24) {
            result = "偏胖";
        }
        else if (bmi >= 18.5) {
            result = "正常";
        }
        else {
            result = "偏瘦";
        }

        return result;
    }

    /*
    public static void main(String[] args) {
        // 方案1：通过main函数由用户直接输入测试
        // 1.输入身高体重
        Scanner scan = new Scanner(System.in);
        System.out.println("please input weight and height:");
        double weight = scan.nextDouble();
        double height = scan.nextDouble();
        // 2.新建一个测试类BMI(weight,height)
        BMI test = new BMI(weight, height);
        // 3.调用被测方法
        String result = test.getBMIType();
        // 4.校验结果
        System.out.println(result);


        // 方案2：通过main函数由构造函数自行设置输入值测试
        // 1.新建一个测试类BMI(weight,height)和保存答案的result变量
        java.BMI test = new java.BMI(0, 0);
        String result = "";
        System.out.println("Begin test:");
        // 2.测试样例1
        test.serParams(64, 1.74);
        result = test.getBMIType();
        System.out.println("test 1: weight=" + test.getWeight() + ", height=" + test.getHeight() + ",result=" + result);
        // 3.测试用例2
        test.serParams(80, 1.74);
        result = test.getBMIType();
        System.out.println("test 2: weight=" + test.getWeight() + ", height=" + test.getHeight() + ",result=" + result);
        // 4.测试用例3
        test.serParams(85, 1.70);
        result = test.getBMIType();
        System.out.println("test 3: weight=" + test.getWeight() + ", height=" + test.getHeight() + ",result=" + result);
        // 5.测试用例4
        test.serParams(55, 1.74);
        result = test.getBMIType();
        System.out.println("test 4: weight=" + test.getWeight() + ", height=" + test.getHeight() + ",result=" + result);
        // 6.测试用例5
        test.serParams(-64, 1.74);
        result = test.getBMIType();
        System.out.println("test 5: weight=" + test.getWeight() + ", height=" + test.getHeight() + ",result=" + result);
        // 7.测试用例6
        test.serParams(64, 174);
        result = test.getBMIType();
        System.out.println("test 6: weight=" + test.getWeight() + ", height=" + test.getHeight() + ",result=" + result);
    }
    */
}
