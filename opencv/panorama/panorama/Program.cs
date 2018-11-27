using System;
using System.Collections.Generic;
using OpenCvSharp;

namespace panorama
{
    class Program
    {
        private static Mat[] SelectStitchingImages(int count)
        {
            var rand = new Random();
            var mats = new List<Mat>();
            for (int i = 0; i < count; i++)
            {
                //var filename = "C:\\Users\\sv06\\Documents\\dir3gui\\dir3gui\\bin\\x86\\Release\\rec\\20181106204016\\" + i.ToString() + ".jpg";
                //var filename = "C:\\Users\\sv06\\Documents\\dir3gui\\dir3gui\\bin\\x86\\Release\\rec\\20181106204550\\" + i.ToString() + ".jpg";
                var filename = "C:\\Users\\sv06\\Documents\\dir3gui\\dir3gui\\bin\\x86\\Release\\rec\\20181107133423\\" + i.ToString() + ".jpg";

                var m = new Mat(filename, ImreadModes.Color);
                mats.Add(m.Clone());
            }

            return mats.ToArray();
        }
        static void Main(string[] args)
        {
            Mat[] images = SelectStitchingImages(10);
            Mat pano = new Mat();
            var stitcher = Stitcher.Create(true);
            Console.Write("Stitching start...");
            var status = stitcher.Stitch(images, pano);
            Console.WriteLine(" finish (status:{0})", status);
            Window.ShowImages(pano);
            foreach (Mat image in images)
            {
                image.Dispose();
            }
            pano.ImWrite("dst.jpg");
        }
    }
}
