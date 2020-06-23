package test;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;

import static org.junit.Assert.*;

/**
 * junit套件测试
 * 1.指定运行器@RunWith(Suite.class)
 * 2.指定要加入的测试类@Suite.SuiteClasses({BMITest2.class, BloodPressureTest.class}),
 * 3.进行套件测试
 */
@RunWith(Suite.class)
@Suite.SuiteClasses({BMITest2.class, BloodPressureTest.class})
public class TestSuiteWithBMIAndBloodPressure {

}