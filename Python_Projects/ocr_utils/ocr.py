CHUNKING_WEIGTH = 12
File = 12

def get_one_with_params(a, id=0):
    return {}

def get_stream_list():
    return 0,0

def get_pdf_structure(files_id):
    files_description_list = []
    output_stream = BytesIO()
    for file_id in files_id:
        file = get_one_with_params(File, id=file_id)

        # HERE get stream and scan_list for this file
        list_str, stream = get_stream_list()
        files_description_list.append({id: file_id, stream: stream, list:list_str})



def chunk_files(folder_id, files_to_chunk_ids, files_id, parent_log):
    # log = get_one_with_params(Log, id=parent_log['id'])
    jobs = []
    nb_files = len(files_to_chunk_ids)
    for file_id in files_id:
        if file_id not in files_to_chunk_ids:
            continue

        # file_chunking = chunk_single_file.delay(file_id, parent_log)
        # job = Job.objects.create(
        #    process_id=file_chunking.id,
        #    log= log,
        #    weigth=CHUNKING_WEIGTH/nb_files
        # )
        # jobs.append(job)

    return jobs


def build_file_list():



if __name__ == "__main__":

