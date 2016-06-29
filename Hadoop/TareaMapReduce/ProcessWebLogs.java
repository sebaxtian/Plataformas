import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;



public class ProcessWebLogs {


    // La Clase Mapper
    public static class WebLogsMapper extends Mapper<Object, Text, Text, IntWritable> {

        // Contador
        private final static IntWritable one = new IntWritable(1);
        // Palabra
        private Text word = new Text();

        // La funcion map
        public void map(Object key, Text value, Context context ) throws IOException, InterruptedException {
            // Cada linea del archivo tsv tiene los siguientes datos separados por tabulado
            // host	logname	time	method	url	response	bytes	referer	useragent
            StringTokenizer itr = new StringTokenizer(value.toString(), "\t");
            // El primer elemento del StringTokenizer es el Host
            if(itr.hasMoreTokens()) {
                String host = itr.nextToken();
                word.set(host);
                // Cuenta cada palabra o nombre de host
                context.write(word, one);
            }
        }
    }


    // La Clase Reducer
    public static class WebLogsReducer extends Reducer<Text,IntWritable,Text,IntWritable> {

        // Numero de ocurrencias
        private IntWritable result = new IntWritable();
        private int maxsum = Integer.MIN_VALUE;

        // La funcion reduce
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            // Suma el numero de ocurrencias
            int sum = 0;
            // Por cada valor suma el numero de ocurrencias asociadas a una key
            for (IntWritable val : values) {
                sum += val.get();
                if(sum > maxsum) {
                    maxsum = sum;
                }
            }

            result.set(maxsum);
            // Numero de ocurrencias de cada palabra o nombre de host
            context.write(key, result);
        }
    }


    // Funcion Main del programa
    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "Process Web Logs");
        job.setJarByClass(ProcessWebLogs.class);
        job.setMapperClass(WebLogsMapper.class);
        job.setCombinerClass(WebLogsReducer.class);
        job.setReducerClass(WebLogsReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }

}
