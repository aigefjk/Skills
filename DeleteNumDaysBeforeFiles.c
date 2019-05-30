/*********************************************************************************************************
 ** Function Name £ºDeleteNumDaysBeforeFiles
 ** Function Usage £ºDelete all specified types of files that created specified days ago
 ** Entry Parameters £ºsearch_path[] ,eg£º"c:\\Users\\Administrator\\Desktop\\ALARM\\"
               file_type[] ,eg£º"*.txt"£¨all ".txt" files£©¡¢"*.*"(all files)
			   num_days_before ,eg£º15£¨delete all specified types of files that created 15 days ago£©
 ** Exit Para£ºnone
 ** Author£ºNovel Fan
 ** Date£º2019/01/04 16:35
 *********************************************************************************************************/
int DeleteNumDaysBeforeFiles(char search_path[],char file_type[],int num_days_before)
{
	int File_Year,File_Month,File_Day,Curr_Year, Curr_Month, Curr_Day;

	char search_file_path[512] = {0};
	char file_path[512] = {0};
	char first_file_name[512] = {0};
	char next_file_name[512] = {0};

	double interval;

	CVIAbsoluteTime Curr_AbsTime,File_AbsTime;
	
	CVITimeInterval result;
	
	int OnceFlag=1,State;
	
	
	GetSystemDate (&Curr_Month, &Curr_Day, &Curr_Year);
	CVIAbsoluteTimeFromLocalCalendar (Curr_Year, Curr_Month, Curr_Day, 0, 0, 0, 0, &Curr_AbsTime);
			
	do
	{
	    if(OnceFlag==1)
		{
			 OnceFlag=0;
			 
			 sprintf(search_file_path,"%s%s",search_path,file_type); 
			 
			 State=GetFirstFile (search_file_path, 1, 0, 0, 0, 0, 0, first_file_name);
			
			 if(State==0)
			 {
				    sprintf(file_path,"%s%s",search_path,first_file_name);  
				
					GetFileDate (file_path, &File_Month, &File_Day, &File_Year);
				
					CVIAbsoluteTimeFromLocalCalendar (File_Year, File_Month, File_Day, 0, 0, 0, 0, &File_AbsTime); 

					SubtractCVIAbsoluteTimes (Curr_AbsTime, File_AbsTime, &result);


					CVITimeIntervalToSeconds (result, &interval);

					if(interval>=3600*24*num_days_before)
					    DeleteFile (file_path);
		
			 }
			 
		}
		else
		{
		
			sprintf(file_path,"%s%s",search_path,next_file_name); 
			
			GetFileDate (file_path, &File_Month, &File_Day, &File_Year);
			
			CVIAbsoluteTimeFromLocalCalendar (File_Year, File_Month, File_Day, 0, 0, 0, 0, &File_AbsTime); 

			SubtractCVIAbsoluteTimes (Curr_AbsTime, File_AbsTime, &result);


			CVITimeIntervalToSeconds (result, &interval);

			if(interval>=3600*24*num_days_before)
			    DeleteFile (file_path);
			
		}
			
		
	}
	while((State==0)&&(GetNextFile(next_file_name)==0));
	
	return 0;
	
}
