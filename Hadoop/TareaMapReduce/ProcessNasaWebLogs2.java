import java.util.*;

import java.io.IOException;
import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.util.*;



public class ProcessNasaWebLogs2 {

    // La Clase Mapper
    public static class WebLogsMapper extends MapReduceBase implements Mapper<LongWritable, Text, Text, IntWritable> {

        // La funcion Map
        public void map(LongWritable key, Text value, OutputCollector<Text, IntWritable> output, Reporter reporter) throws IOException {
            // Cada linea del archivo tsv tiene los siguientes datos separados por tabulado
            // host	logname	time	method	url	response	bytes	referer	useragent
            String line = value.toString();
            StringTokenizer s = new StringTokenizer(line, "\t");
            // El primer elemento del StringTokenizer es el Host
            String host = s.nextToken();
            s.nextToken(); // logname
            s.nextToken(); // time
            s.nextToken(); // method
            // Valida que sea el host mas visitado
            if(host.equals("130.110.74.81")) {
                // El cuarto elemento del StringTokenizer es la URL
                String url = s.nextToken();
                // Cuenta cada nombre de url
                output.collect(new Text(url), new IntWritable(1));
            }
        }

    }



    // La Clase Reducer
    public static class WebLogsReducer extends MapReduceBase implements Reducer<Text, IntWritable, Text, IntWritable> {

        // La llave que tiene el valor maximo
        private Text keymax;
        // El valor maximo
        private int valuemax = Integer.MIN_VALUE;

        // La funcion Reduce
        public void reduce( Text key, Iterator <IntWritable> values, OutputCollector<Text, IntWritable> output, Reporter reporter) throws IOException {
            // Numero de ocurrencias de cada nombre de url
            int ocurrencias = 0;
            while (values.hasNext()) {
                ocurrencias += values.next().get();
            }
            // Actualiza la llave y valor para el numero de ocurrencias maximo
            if(ocurrencias > valuemax) {
                keymax = key;
                valuemax = ocurrencias;
                // Numero de ocurrencias maximo de nombre de url
                output.collect(keymax, new IntWritable(valuemax));
            }
        }

    }


    // Funcion Main del programa
    public static void main(String args[])throws Exception {

        JobConf conf = new JobConf(ProcessNasaWebLogs2.class);
        conf.setJobName("ProcessNasaWebLogs2");
        conf.setOutputKeyClass(Text.class);
        conf.setOutputValueClass(IntWritable.class);
        conf.setMapperClass(WebLogsMapper.class);
        conf.setCombinerClass(WebLogsReducer.class);
        conf.setReducerClass(WebLogsReducer.class);
        conf.setInputFormat(TextInputFormat.class);
        conf.setOutputFormat(TextOutputFormat.class);
        FileInputFormat.setInputPaths(conf, new Path(args[0]));
        FileOutputFormat.setOutputPath(conf, new Path(args[1]));

        JobClient.runJob(conf);
    }

}
