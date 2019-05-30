        void DeleteExpiredFiles()
        {
       

            strFolderPath = "D:\\LogFiles\\";
            dyInfo = new DirectoryInfo(strFolderPath);
            
            foreach (FileInfo feInfo in dyInfo.GetFiles("*.log"))
            {
              
                if (feInfo.LastWriteTime.AddDays(90) < DateTime.Today)
                    feInfo.Delete();
            }




        }
