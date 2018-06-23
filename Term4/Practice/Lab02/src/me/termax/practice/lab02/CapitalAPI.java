package me.termax.practice.lab02;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CapitalAPI {
    public static String getCapital(String countryName) {
        try {
            URL url = new URL("http://restcountries.eu/rest/v2/name/"+countryName+"?fields=capital");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.addRequestProperty("User-Agent", "Mozilla/4.76");
            connection.setRequestMethod("GET");

            BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String inputLine;
            StringBuilder response = new StringBuilder();

            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine);
            }
            in.close();
            Pattern p = Pattern.compile("\"capital\":\"(.*?)\"");
            Matcher m = p.matcher(response.toString());
            if (m.find()) {
                return m.group(1);
            }
        } catch (Exception e) {
            return null;
        }
        return null;
    }
}
