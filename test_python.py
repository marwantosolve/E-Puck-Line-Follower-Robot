from controller import Robot, Motor, DistanceSensor

TIME_STEP = 64  # نفس قيمة الفاصل الزمني

# إنشاء كائن الروبوت
robot = Robot()

# الحصول على المحركات
motor_right = robot.getDevice("right wheel motor")
motor_left = robot.getDevice("left wheel motor")

# تعيين وضعية الدوران اللانهائي للمحركات
motor_right.setPosition(float('inf'))
motor_left.setPosition(float('inf'))

# تهيئة الحساسات
sensor_right = robot.getDevice("right_sensor")
sensor_left = robot.getDevice("left_sensor")

# تفعيل الحساسات
sensor_right.enable(TIME_STEP)
sensor_left.enable(TIME_STEP)

# إعدادات التحكم
base_speed = 2.5  # السرعة الأساسية
Kp = 0.005        # معامل التعديل؛ يمكن تعديله حسب الحاجة لتحسين الاستجابة

while robot.step(TIME_STEP) != -1:
    # قراءة قيم الحساسات
    value_right = sensor_right.getValue()
    value_left = sensor_left.getValue()
    
    # طباعة القيم لمراقبة الأداء
    print(f"Right: {value_right:.2f}, Left: {value_left:.2f}")
    
    # حساب الخطأ بناءً على الفرق بين قراءة الحساسين
    # نفترض أن انخفاض قيمة الحساس يدل على مرور الخط (مثلاً لون داكن)
    error = value_right - value_left
    adjustment = Kp * error
    
    # تعديل السرعات بناءً على الخطأ
    speed_left = base_speed + adjustment
    speed_right = base_speed - adjustment
    
    # التأكد من عدم توريد سرعات سالبة (يمكن تعديل هذا حسب احتياجات الروبوت)
    speed_left = max(0, speed_left)
    speed_right = max(0, speed_right)
    
    # ضبط سرعات المحركات
    motor_left.setVelocity(speed_left)
    motor_right.setVelocity(speed_right)

# تنظيف الموارد (اختياري في Python)
robot.cleanup()
