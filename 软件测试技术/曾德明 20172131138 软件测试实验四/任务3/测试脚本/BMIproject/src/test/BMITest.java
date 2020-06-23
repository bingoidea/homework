package test;

import main.BMI;
import org.junit.After;
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

    // before方法在每个测试用例执行前执行一次
    @org.junit.Before
    public void setUp() throws Exception {
        // 在这里创建被测对象
        testObj = new BMI(64, 1.74);
    }

    // after方法在每个测试用例执行后执行一次
    @org.junit.After
    public void tearDown() throws Exception {
        // 在这里销毁被测对象
        testObj = null;
    }

    // 测试用例1：正常
    @org.junit.Test
    public void getBMIType_Normal() {
        // 创建测试对象
        testObj.serParams(64, 1.74);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "正常"; // 期望结果
        assertTrue(expect == result);
    }

    // 测试用例2：偏胖
    @org.junit.Test
    public void getBMIType_SlightlyFat() {
        // 创建测试对象
        testObj.serParams(80, 1.74);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "偏胖"; // 期望结果
        assertTrue(expect == result);
    }

    // 测试用例3：肥胖
    @org.junit.Test
    public void getBMIType_Fat() {
        // 创建测试对象
        testObj.serParams(85, 1.70);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "肥胖"; // 期望结果
        assertTrue(expect == result);
    }

    // 测试用例4：偏瘦
    @org.junit.Test
    public void getBMIType_Thin() {
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
        // 创建测试对象
        testObj.serParams(64, 174);
        // 调用测试方法
        String result = testObj.getBMIType();
        // 校验测试结果
        String expect = "输入身高单位应为米!"; // 期望结果
        assertTrue(expect == result);
    }
}