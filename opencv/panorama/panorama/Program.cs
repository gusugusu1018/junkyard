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
                var filename = "C:\\Users\\sv06\\Documents\\junkyard\\opencv\\panorama\\srck" + i.ToString() + ".JPG";
                var m = new Mat(filename, ImreadModes.Color);
                mats.Add(m.Clone());
            }

            return mats.ToArray();
        }
        static void Main(string[] args)
        {
            Mat[] images = SelectStitchingImages(4);
            Mat pano = new Mat();
            var stitcher = Stitcher.Create(false);
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
