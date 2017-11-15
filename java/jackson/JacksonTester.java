import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.annotation.JsonInclude;

import org.springframework.http.converter.json.Jackson2ObjectMapperBuilder;

import lombok.Getter;
import lombok.Setter;
import lombok.AllArgsConstructor;

enum Color {
    RED, BLUE, BLACK, YELLO, GREEN
}

class Base {
    protected @Getter @Setter String base;
}

// @AllArgsConstructor
public class JacksonTester extends Base {
    private @Getter String name;
    private @Getter String contact;
    private @Getter Color color;
/*
    @JsonCreator
    public JacksonTester(@JsonProperty("name") final String name,
            @JsonProperty("color") final Color color,
            @JsonProperty("contact") final String contact) {
        this.name = name;
        this.contact = contact;
        this.color = color;
    }
    */

    public static void main(String[] args) throws Exception {
        ObjectMapper OM = new ObjectMapper();
        final String json = "{\"name\":\"xingrui\",\"contact\":\"12345678901\", \"color\":\"RED\",\"base\":\"123456\"}";
        JacksonTester tester = OM.readValue(json, JacksonTester.class);
        System.out.println(tester.name);
        System.out.println(tester.contact);
        tester.contact = null;
        new Jackson2ObjectMapperBuilder().serializationInclusion(JsonInclude.Include.NON_NULL).configure(OM);
        System.out.println(OM.writeValueAsString(tester));

        ObjectMapper OM2 = new ObjectMapper();
        System.out.println(OM2.writeValueAsString(tester));
    }
}
