package me.termax.practice.lab04;

import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Orientation;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;



public class Main extends Application {

    private Pattern currentPattern;
    private Map<String, Pattern> patternMap;
    private Label status;
    private TextField textField;

    private void updateStatus(String text) {
        status.setTextFill(currentPattern.matcher(text).matches()?Color.GREEN:Color.RED);
    }

    @Override
    public void start(Stage primaryStage) {

        patternMap = new HashMap<String, Pattern>() {{
            put("Natural number", Pattern.compile("[1-9]\\d*"));
            put("Integer", Pattern.compile("([+-]?[1-9]\\d*|0)"));
            put("Float", Pattern.compile("[+-]?((\\d+\\.\\d*)|(\\d*\\.?\\d+))([eE][-+]?\\d+)?"));;
            put("Date", Pattern.compile("(((0[1-9]|[12][0-9]|3[01])\\.(0[13578]|10|12))|((0[1-9]|[12][0-9]|30)\\.(0[469]|11))|((0[1-9]|[12][0-9])\\.02))\\.(19|20)\\d\\d"));
            put("Time", Pattern.compile("([01]?[0-9]|2[0-3])[: ][0-5][0-9]([: ][0-5][0-9])?"));
            put("Email", Pattern.compile("(\\w+\\.?)+@(\\w+_?)+\\.\\w{2,}"));
        }};

        final ComboBox<String> patternSelect = new ComboBox<>();
        patternSelect.getItems().addAll(
                "Natural number",
                "Integer",
                "Float",
                "Date",
                "Time",
                "Email"
        );

        status = new Label("\uD83C\uDF11");
        status.setTextFill(Color.RED);

        textField = new TextField ();
        textField.textProperty().addListener((observable, oldValue, newValue) -> updateStatus(newValue));

        patternSelect.valueProperty().addListener((observable, oldValue, newValue) -> {
            currentPattern = patternMap.get(newValue);
            updateStatus(textField.getText());
        });
        patternSelect.setValue("Natural number");

        ListView<String> dates = new ListView<>();
        dates.setPrefWidth(100);

        TextArea textArea = new TextArea();
        textArea.setPrefWidth(215);
        textArea.textProperty().addListener((observable, oldValue, newValue) -> {
            dates.getItems().clear();
            Matcher m = patternMap.get("Date").matcher(newValue);
            while (m.find())
                dates.getItems().add(m.group());
        });



        HBox task1 = new HBox();
        task1.setSpacing(10);
        task1.getChildren().addAll(patternSelect, textField, status);

        HBox task2 = new HBox();
        task2.setSpacing(5);
        task2.getChildren().addAll(textArea, dates);

        VBox root = new VBox();
        root.setSpacing(30);
        root.getChildren().addAll(task1, task2);

        Scene scene = new Scene(root, 320, 200);
        primaryStage.setTitle("Lab 4");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
    public static void main(String[] args) {
        launch(args);
    }
}