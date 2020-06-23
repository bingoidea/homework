package test;

import main.BMI;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;

import static org.junit.Assert.*;

/**
 * junit参数化测试（构造器注入）
 */
// 1.指定参数化运行器
@RunWith(Parameterized.class)
public class BMITest2 {
    // 声明被测类
    BMI testObj;

    // 2.定义参数:定义私有变量，用于保存输入和预期输出
    private double weightForTest;   // 体重
    private double heightForTest;   // 身高
    private String expected;        // 预期输出

    // 3.引入参数:定义带参数的构造方法
    public BMITest2(double weightForTest, double heightForTest, String expected) {
        this.weightForTest = weightForTest;
        this.heightForTest = heightForTest;
        this.expected = expected;
    }

    // 4.准备测试数据:声明一个使用注解 org.junit.runners.Parameterized.Parameters 修饰的，返回值为 java.util.Collection 的公共静态方法，并在此方法中初始化所有需要测试的参数对
    // 该方法必须由Parameters注解修饰；（2）该方法必须为public static的；（3）该方法必须返回Collection类型；（4）该方法的名字不做要求；（5）该方法没有参数
    // 可读性提升，@Parameterized.Parameters(name = "{index}:function[{0}]={1}")，name固定，index是测试用例序号，function是被测方法，后面是参数序号
    @Parameterized.Parameters(name = "{index}:getBMIType[{0},{1}]={2}")
    public static Collection testDataset(){
        return Arrays.asList( new Object[][]{
                {62.0, 1.74, "正常"},
                {80.0, 1.74, "偏胖"},
                {85.0, 1.70, "肥胖"},
                {55.0, 1.74, "偏瘦"},
                {-64.0, 1.74, "输入错误!"},
                {64.0, 174.0, "输入身高单位应为米!"}
        });
    }

    // 5.下面编写测试方法
    @Before
    public void setUp() throws Exception {
        // 使用setUp进行测试对象创建(用已有的私有参数进行创建)
        testObj = new BMI(weightForTest, heightForTest);
    }

    @After
    public void tearDown() throws Exception {
        // 使用tearDown进行测试对象的销毁
        testObj = null;
    }

    @Test
    public void getBMIType() {
        // 测试方法本体(用预期结果对比测试结果)
        assertTrue(expected == testObj.getBMIType());
    }
}