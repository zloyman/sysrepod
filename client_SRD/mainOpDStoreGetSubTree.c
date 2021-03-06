/*
 * mainOpDStoreGetSubTree.c
 *
 * License: Apache 2.0
 *
 *  Created on: March 25, 2015
 *      Creator: Niraj Sharma
 *      Cisco Systems, Inc.
 *
 */

#define MAIN_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "srd.h"

#define MSGLENFIELDWIDTH 7

int main(int argc, char**argv)
{
   int sockfd;
   char defaultServerIP []="127.0.0.1";
   char *serverIP;
   int serverPort = SRD_DEFAULTSERVERPORT;
   char opDataStoreName [100];
   char xpath[100];
   char *value = NULL;

   if (argc != 2)
      serverIP = defaultServerIP;
   else
      serverIP = argv[1];

   if (!srd_connect (serverIP, serverPort, &sockfd)){
	   printf ("Error in connecting to server %s at port %d\n", serverIP, serverPort);
	   exit (1);
   }

   /*
    * Get the first sub tree - it is specified by using the path to it to set the value
    * of Op Data Store Name
    */
   strcpy (opDataStoreName, "urn:ietf:params:xml:ns:yang:ietf-interfaces/interfaces");
   // strcpy (xpath, "/packet_stats/*");
   strcpy(xpath, "/*/*[local-name()='interfaces']");
   srd_applyXPathOpDataStore (sockfd, opDataStoreName, xpath, &value);
   if (value){
	   printf ("Result of XPATH '%s' on Operational Data Store %s is : %s\n", xpath, opDataStoreName, value);
	   free (value);
   } else {
	   printf ("Result of XPath '%s' on Operational Data Store %s is NULL.\n", xpath, opDataStoreName);
   }

   /*
    * Get the second sub tree, this request will go to a different south-side daemon
    */

   strcpy (opDataStoreName, "urn:ietf:params:xml:ns:yang:ietf-interfaces/interfaces-state");
      // strcpy (xpath, "/packet_stats/*");
      strcpy(xpath, "/*/*[local-name()='interfaces-state']");
      srd_applyXPathOpDataStore (sockfd, opDataStoreName, xpath, &value);
      if (value){
   	   printf ("Result of XPATH '%s' on Operational Data Store %s is : %s\n", xpath, opDataStoreName, value);
   	   free (value);
      } else {
   	   printf ("Result of XPath '%s' on Operational Data Store %s is NULL.\n", xpath, opDataStoreName);
      }

   srd_disconnect (sockfd); // disconnect this client, leave server running
   // srd_terminateServer (sockfd); // terminate server and disconnect this client
   xmlCleanupParser();
   exit (0);
}

