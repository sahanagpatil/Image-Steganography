#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("Invalid command,please enter valid command\n");
        return 0;
    }
    //structure variable define
    EncodeInfo encInfo;
    DecodeInfo decInfo;
   
    // collect the result from check operation 
    int res = check_operation_type(argv);
    
        //res if 0 or e_encode
        if(res == e_encode)
        {
            if(argc < 4)
                {
                    printf("Invalid command,please enter valid command\n");
                    return 0;
                }
            //check argc value may vary from 4 to 5
            if(argc>=4 && argc<=5)
            {   
                //check read and validate encode validation
                if(read_and_validate_encode_args(argv,&encInfo) == e_failure)
                {

                    printf("Invalid command,please enter valid command\n");
                    return 0;
                    
                }
                //do encoding  if not equal to failure
                if(do_encoding(&encInfo) == e_failure)
                {
                    printf("Error in Encoding\n");
                    return 0;
                }
            //if all condition false then encoding done
            printf("Encoding Done Successfully\n");
            }
        }
        
        else
        {
            // res equal to 1 or -d -> e_decode
         if(res == e_decode)
            {
                if(argc < 3)
                {
                    printf("Invalid command,please enter valid command\n");
                    return 0;
                }
                 if(read_and_validate_decode_args(argv,&decInfo) == e_failure)
                {

                    printf("Invalid command,please enter valid command\n");
                    return 0;
                    
                }
                //do decoding  if not equal to failure
                if(do_decoding(&decInfo) == e_failure)
                {
                    printf("Error in Decoding\n");
                    return 0;
                }
            }
            else
            {
                // if not print error msg
            printf("Error in Decoding\n");
                    return 0;
            }
                //if all condtions are false decoding done
            printf("Decoding Done Successfully\n");

        }
            
}
        
OperationType check_operation_type(char *argv[])
{

    //check argv[1] -e or not
    if(strcmp(argv[1],"-e")==0)
    {
        return e_encode;
    }
    //check argv[1] -d or not
    else if(strcmp(argv[1],"-d")==0)
    {
            return e_decode;
    }
    else
    
    {       // if not both it will take it has e_unsupported
            return e_unsupported;
    }
}


