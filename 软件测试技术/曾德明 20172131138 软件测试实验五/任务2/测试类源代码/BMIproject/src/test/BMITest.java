package test;

import main.BMI;
import org.junit.After;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runners.Parameterized;

import java.util.Collection;

import static org.junit.Assert.*;

/**
 * 方案3 通过junit测试
 */
public class BMITest {
    // 声明被测类
    BMI testObj;

    // before方法在每个测试用例@test执行前执行一次，必须声明为public
    @org.junit.Before
    public void setUp() throws Exception {
        System.out.println("run @before method");
        // 在这里创建被测对象
        testObj = new BMI(64, 1.74);
    }

    // after方法在每个测试用例@test执行前执行一次，必须声明为public
    @org.junit.After
    public void tearDown() throws Exception {
        System.out.println("run @after method");
        // 在这里销毁被测对象
        testObj = null;
    }

    // beforeclass方法只会在类中定义一次，执行一次，且一定是在所有测试样例之前，必须声明为public static
    @org.junit.BeforeClass
    public static void prepareEnvironment() {
        System.out.println("run @beforeclass method");
    }

    // afterclass方法只会在类中定义一次，执行一次，且一定是在所有测试样例之后，必须声明为public static
    @org.junit.AfterClass
    public static void restoreEnvironment() {
        System.out.println("run @afterclass method");
    }

    // 测试用例1：正常
    @org.junit.Test
    public void getBMIType_Normal() {
        System.out.println("run @test getBMIType_Normal");
        // 创建测试对象
        testObj.serParams(64, 1.74);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "正常"; // 期望结果
        assertTrue(expect == result); // 断言一个条件为真
    }

    // 测试用例2：偏胖
    @org.junit.Test
    public void getBMIType_SlightlyFat() {
        System.out.println("run @test getBMIType_SlightlyFat");
        // 创建测试对象
        testObj.serParams(80, 1.74);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "偏胖"; // 期望结果
        assertEquals(expect, result); // 断言两个值相等
        // assertTrue(expect == result);
    }

    // 测试用例3：肥胖
    @org.junit.Test
    public void getBMIType_Fat() {
        System.out.println("run @test getBMIType_Fat");
        // 创建测试对象
        testObj.serParams(85, 1.70);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "肥胖"; // 期望结果
        assertFalse(expect != result); // 判断一个条件为假
        // assertTrue(expect == result);
    }

    // 测试用例4：偏瘦
    @org.junit.Test
    public void getBMIType_Thin() {
        System.out.println("run @test getBMIType_Thin");
        // 创建测试对象
        testObj.serParams(55, 1.74);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "偏瘦"; // 期望结果
        assertTrue(expect == result);
    }

    // 测试用例5：输入错误!
    @org.junit.Test
    public void getBMIType_InputError() {
        System.out.println("run @test getBMIType_InputError");
        // 创建测试对象
        testObj.serParams(-64, 1.74);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "输入错误!"; // 期望结果
        assertTrue(expect == result);
    }

    // 测试用例6：输入身高单位应为米!
    @org.junit.Test
    public void getBMIType_Inputillegal() {
        System.out.println("run @test getBMIType_Inputillegal");
        // 创建测试对象
        testObj.serParams(64, 174);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "输入身高单位应为米!"; // 期望结果
        assertTrue(expect == result);
    }
}