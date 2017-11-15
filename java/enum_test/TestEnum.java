enum Type {
    JOIN,QUIT,SCHEDULE,TASK
}

enum StringEnumOther {
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY;
}

// StringEnum类的功能通过StringEnumOther类完全可以实现，除非想要枚举的名称和字符串不一样的情况。
// 但如果真的是这样的话，为什么不修改枚举的名称呢？
enum StringEnum {
    MONDAY("MONDAY"),
    TUESDAY("TUENDAY"),
    WEDNESDAY("WEDNESDAY"),
    THURSDAY("THURSDAY"),
    FRIDAY("FRIDAY"),
    SATURDAY("SATURDAY"),
    SUNDAY("SUNDAY");
    private final String text;

    private StringEnum(final String text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return text;
    }
}

public class TestEnum {
    public static void main(String[] args) {
        Type t = Type.JOIN;
        System.out.println(t.ordinal());
        StringEnum stringEnum = StringEnum.MONDAY;
        StringEnumOther stringEnumOther = StringEnumOther.MONDAY;
        System.out.println(stringEnum);
        System.out.println(stringEnum.ordinal());
        System.out.println(stringEnumOther);
        System.out.println(stringEnumOther.ordinal());
    }
}
