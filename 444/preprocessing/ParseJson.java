import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Date;
import java.lang.Math;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.Calendar;
import org.json.JSONObject;
import org.json.JSONArray;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.TreeMap;
import java.util.Map;

public class ParseJson {
//CONFIG VARIABLES
//------------------------------------------------------------------------------
    public static final float CONFIDENCE_THRESHOLD = 0.7f;
    public static final int YEAR_THRESHOLD_LOWER = 1990;
    public static final int YEAR_THRESHOLD_UPPER = 2015;
//------------------------------------------------------------------------------

//Bookkeeping variables
//------------------------------------------------------------------------------
    public static int[][] mapGrid = new int[10][10];
    public static BufferedWriter[][] mapGridWriters = new BufferedWriter[10][10];

    public static int oldestYear = 2016, newestYear;
    public static long oldestYearMillis, newestYearMillis;

    public static int[] dateFrequencies = new int[(YEAR_THRESHOLD_UPPER - YEAR_THRESHOLD_LOWER) + 1];
    public static TreeMap<String, Integer> followerCounts = new TreeMap<>();
//------------------------------------------------------------------------------

    public static void main(String... args) {
        try {
            if(args.length != 2) {
                System.out.println("Must provide 2 input files as <users file> <images file>");
                return;
            }

            getUsers(args[0]);

            //example to get a user's follower count
            if(followerCounts.containsKey("99994466@N04")) {
                System.out.println("99994466@N04 has " + followerCounts.get("99994466@N04") + " followers");
            }
            else {
                System.out.println("99994466@N04 has 0 followers");
            }
            
            createBufferedWriters();
            sortByGeolocation(args[1]);
            closeBufferedWriters();
            sortGeolocationsByDate();
            printResults();
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }

    public static void getUsers(String fileName) {
        readFile(makeFile(fileName), new OnLineReadListener() {
            public void onLineRead(String line) {
                try {
                    JSONObject jsonObject = new JSONObject(line);
                    JSONArray following = jsonObject.getJSONArray("following");

                    for(int i = 0; i < following.length(); i++) {
                        JSONObject user = following.getJSONObject(i);
                        String userId = user.getString("userId");
                        if(followerCounts.containsKey(userId)) {
                            Integer currentValue = followerCounts.get(userId);
                            followerCounts.put(userId, (currentValue + 1));
                        }
                        else {
                            followerCounts.put(userId, 1);
                        }
                    }
                }
                catch(Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

//Read in single input file, remove unnecessary JSON keys, remove machine tags 
//with low confidence, and write to file according to its geolocation.
//------------------------------------------------------------------------------
    public static void sortByGeolocation(String fileName) {
        readFile(makeFile(fileName), new OnLineReadListener() {
            public void onLineRead(String line) {
                try {
                    //get JSON representation of the record at this line
                    JSONObject jsonObject = new JSONObject(line);

                    //transfer the time in millis to a more usable representation
                    long millis = jsonObject.getLong("dateTaken");
                    Calendar cal = Calendar.getInstance();
                    cal.setTimeInMillis(millis);
                    int year = cal.get(Calendar.YEAR);
                    int month = cal.get(Calendar.MONTH);
                    int day = cal.get(Calendar.DAY_OF_MONTH);
                    JSONObject dateTaken = new JSONObject();
                    dateTaken.put("year", year);
                    dateTaken.put("month", month);
                    dateTaken.put("day", day);
                    jsonObject.put("date", dateTaken);
                    JSONObject follow_count = new JSONObject();
                    JSONObject user =  jsonObject.getJSONObject("user");
                    String id = user.getString("id");
                    //System.out.println(id);
                    int count;
                    if(followerCounts.get(id)==null)
                        count=0;
                    else{
                        count = followerCounts.get(id);
                        //System.out.println(count);
                    }
                    jsonObject.put("followCount", count);
                    JSONArray favorite = jsonObject.getJSONArray("favorites");
                    int num_f;
                    num_f = favorite.length();
                    jsonObject.put("favoriteCount",num_f);
                    //some dates are messed up, having years that make no sense, like 9 or 4500
                    //Set a threshold and don't continue with any more processing on items
                    //that fall outside this date range
                    if(year < YEAR_THRESHOLD_LOWER || year > YEAR_THRESHOLD_UPPER) return;

                    if(year < oldestYear) {
                        oldestYear = year;
                        oldestYearMillis = millis;
                    }
                    if(year > newestYear) {
                        newestYear = year;
                        newestYearMillis = millis;
                    }

                    dateFrequencies[year - YEAR_THRESHOLD_LOWER]++;

                    //Iterate over all keys in the object and remove anything that 
                    //isn't one of the keys we explicitly want to keep
                    Iterator<String> iterator = jsonObject.keys();
                    ArrayList<String> keysToRemove = new ArrayList<>();

                    while(iterator.hasNext()) {
                        String key = iterator.next();
                        if(
                            !key.equals("date") &&
                            !key.equals("machineTags") &&
                            !key.equals("downloadUrl") &&
                            !key.equals("geo")&&
                            !key.equals("followCount")&&
                            !key.equals("favoriteCount"))
                        {
                            keysToRemove.add(key);
                        }
                    }

                    for(String key : keysToRemove) {
                        jsonObject.remove(key);
                    }
                    
                    //filter out tags whose confidence number is lower than 0.7a
                    Iterator itr = jsonObject.getJSONArray("machineTags").iterator();
                    while (itr.hasNext()) {
                        JSONObject obj = (JSONObject) itr.next();
                        if (obj.getDouble("confidence") < CONFIDENCE_THRESHOLD) {
                            itr.remove();
                        }
                    }
                    
                    //Get the location of this photo, calculate which grid position it should be at,
                    //and write it to the file representing that grid location
                    JSONObject geo = jsonObject.getJSONObject("geo");
                    double lat = geo.getDouble("latitude");
                    double lon = geo.getDouble("longtitude");
                    int x = (int) Math.floor((lon + 180)/36);
                    int y = (int) Math.floor((lat + 90)/18);

                    mapGridWriters[x][y].write(jsonObject.toString() + "\n");
                    mapGrid[x][y]++;
                }
                catch(Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    public static void createBufferedWriters() {
        try {
            File folder = makeFolder("outputs");
            for(File file: folder.listFiles()) 
                file.delete();

            for(int x = 0; x < 10; x++) {
                for(int y = 0; y < 10; y++) {
                    mapGridWriters[x][y] = createBufferedWriter(getFileAtLocation(x, y), false);
                }
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }

    public static void closeBufferedWriters() {
        try {
            for(int x = 0; x < 10; x++) {
                for(int y = 0; y < 10; y++) {
                    mapGridWriters[x][y].close();
                }
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }

//Read an entire file into memory and sort it by year, then write it back to the same file
//------------------------------------------------------------------------------
    public static void sortGeolocationsByDate() {
        try {
            for(int x = 0; x < 10; x++) {
                for(int y = 0; y < 10; y++) {
                    sortFile(getFileAtLocation(x, y));
                }
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }

    public static void sortFile(File file) {
        try {

            //read in file and add parsed JSONObjects to ArrayList to be sorted
            ArrayList<JSONObject> jsonValues = new ArrayList<JSONObject>();
            readFile(file, new OnLineReadListener() {
                public void onLineRead(String line) {
                    try {
                        //get JSON representation of the record at this line
                        jsonValues.add(new JSONObject(line));
                    }
                    catch(Exception e) {
                        e.printStackTrace();
                    }
                }
            });

            //clear contents of file now that we have read it into memory
            new PrintWriter(file).close();

            //sort the list
            Collections.sort(jsonValues, new Comparator<JSONObject>() {
                //You can change "Name" with "ID" if you want to sort by ID
                private static final String KEY_NAME = "Name";

                @Override
                public int compare(JSONObject a, JSONObject b) {
                    try {
                        JSONObject dateA = a.getJSONObject("date");
                        JSONObject dateB = b.getJSONObject("date");

                        int yearA = dateA.getInt("year");
                        int yearB = dateB.getInt("year");
                        return yearA - yearB;
                    } 
                    catch (Exception e) {
                        return Integer.MAX_VALUE;
                    }
                }
            });

            //write the list back to the same file
            BufferedWriter writer = createBufferedWriter(file, false);
            for (int i = 0; i < jsonValues.size(); i++) {
                JSONObject jsonObject = jsonValues.get(i);

                writer.write(jsonObject.toString() + "\n");
            }
            writer.close();
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }


//Print results after everything is done
//------------------------------------------------------------------------------
    public static void printResults() {
        int totalEntries = 0;
        System.out.println("\n\n");
        System.out.println("Number of entries in each file in the grid");

        //print the grid depecting where in the world we have images
        for(int x = 0; x < 10; x++) {
            for(int y = 0; y < 10; y++) {
                System.out.print("[" + String.format("%1$-" + 6 + "s", mapGrid[x][y]) + "]");
                totalEntries += mapGrid[x][y];
            }
            System.out.print("\n");
        }
        System.out.print("\n");

        //print a timeline showing when we have images
        System.out.println("Number of images for each year regardless of location");
        for(int i = 0; i < dateFrequencies.length; i++) {
            System.out.print("[" + String.format("%1$-" + 6 + "s", (YEAR_THRESHOLD_LOWER + i)) + "]");
            System.out.print("[" + String.format("%1$-" + 6 + "s", dateFrequencies[i]) + "]");
            System.out.print("\n");
        }

        System.out.println("\nTOTAL ENTRIES: " + totalEntries + "\n\n");
    }
    
//General purpose utility functions
//------------------------------------------------------------------------------
    public static final File getFileAtLocation(int x, int y) {
        File folder = makeFolder("outputs");

        File file = makeFile(folder, "data_" + x + "_" + y + ".json");

        return file;
    }

    public static void readFile(File file, OnLineReadListener listener) {
        try {
            FileReader reader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(reader);

            String line;
            while(true) {
                line = bufferedReader.readLine();
                if(line != null)
                    listener.onLineRead(line);
                else
                    break;
            }
            bufferedReader.close();
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }

    public static BufferedWriter createBufferedWriter(File file, boolean append) {
        try {
            return new BufferedWriter(new FileWriter(file, append));
        }
        catch(Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static File makeFile(String fileName) {
        try {
            File file = new File(fileName);
            if (!file.exists())
                file.createNewFile();
            return file;
        }
        catch(Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static File makeFile(File folder, String fileName) {
        try {
            File file = new File(folder, fileName);
            if (!file.exists())
                file.createNewFile();
            return file;
        }
        catch(Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static File makeFolder(String folderName) {
        try {
            File folder = new File(folderName);
            if (!folder.exists())
                folder.mkdir();
            return folder;
        }
        catch(Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static interface OnLineReadListener {
        public void onLineRead(String line);
    }
}
