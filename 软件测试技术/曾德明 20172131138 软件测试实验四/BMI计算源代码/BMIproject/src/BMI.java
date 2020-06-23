import java.util.Scanner;

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
    public BMI(double weight, double height) {
        this.weight = weight;
        this.height = height;
    }

    // 定义功能方法：计算BMI
    public String getBMIType() {
        String result = "";
        double bmi = this.weight / (this.height * this.height);

        if (bmi <= 0) {
            return result = "输入错误!";
        }

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

    public static void main(String[] args) {
        // 方案1：通过main函数直接测试
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
    }
}
