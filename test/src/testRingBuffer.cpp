#include <gtest/gtest.h>

#include <libProducerConsumer.h>

static const char * static_string_producer(bool consumed, char * value, int id) {
    static int current_id = 0;
    static char string_back[10][4];

    // If things are still waiting and we don't have space
    // bail...
    if(!consumed && current_id == 4) {
        return NULL;
    }

    // IF the strings have been consumed we can go back to the start
    if(consumed || current_id == 4) {
        current_id = 0;
    }

    char * str = string_back[current_id++];
    sprintf(str,"%s:%d", value,id);

    return str;
}


TEST(ring_buffer, test_that_ring_allocation_works)
{
    ring_buffer_t rb;

    ring_buffer_err_t er = rb_init(&rb, 6 ^ 2);

    ASSERT_EQ(er, RB_ERR_OK);
    ASSERT_EQ(6 ^ 2, rb.size);

    rb_teardown(&rb);
}

TEST(ring_buffer, test_ring_buffer_can_add)
{
    ring_buffer_t rb;

    ring_buffer_err_t er = rb_init(&rb, 4);

    ASSERT_EQ(er, RB_ERR_OK);

    rb_add(&rb, 1);
    rb_add(&rb, 2);
    rb_add(&rb, 3);
    rb_add(&rb, 4);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_FULL, er);

    ASSERT_EQ(1, rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(2, rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(3, rb_get(&rb));

    // Read past the ast element
    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_NO_DATA, er);

    ASSERT_EQ(0, rb_get(&rb));
    ASSERT_EQ(0, rb_get(&rb));
    ASSERT_EQ(0, rb_get(&rb));

    rb_add(&rb, 1);
    rb_add(&rb, 2);
    rb_add(&rb, 3);
    rb_add(&rb, 4);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_FULL, er);

    ASSERT_EQ(1, rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(2, rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(3, rb_get(&rb));

    // Read past the ast element
    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_NO_DATA, er);

    ASSERT_EQ(0, rb_get(&rb));
    ASSERT_EQ(0, rb_get(&rb));
    ASSERT_EQ(0, rb_get(&rb));

    rb_teardown(&rb);
}

TEST(ring_buffer, test_big_ring_buffer)
{

    ring_buffer_t rb;
    size_t size = 134217728; // 2^27

    ring_buffer_err_t er = rb_init(&rb, size);

    ASSERT_EQ(er, RB_ERR_OK);

    rb_teardown(&rb);
}

TEST(ring_buffer, test_power_of_two)
{
    size_t p = get_power_of_two(31);

    ASSERT_EQ(32, p);

    p = get_power_of_two(37);

    ASSERT_EQ(64, p);
}

TEST(ring_buffer, test_defualt_ring_buffer)
{
    ring_buffer_t rb;
    ring_buffer_err_t er = rb_init_default(&rb);

    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(RING_BUFFER_SIZE, rb.size);

    rb_teardown(&rb);
}

TEST(ring_buffer, test_static_allocation)
{
    STATIC_BUFFER(3, rb);

    rb_add(&rb, 1);
    rb_add(&rb, 2);
    rb_add(&rb, 3);
    rb_add(&rb, 4);

    ring_buffer_err_t er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_FULL, er);

    ASSERT_EQ(1, rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(2, rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(3, rb_get(&rb));

    // Read past the ast element
    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_NO_DATA, er);

    ASSERT_EQ(0, rb_get(&rb));
    ASSERT_EQ(0, rb_get(&rb));
    ASSERT_EQ(0, rb_get(&rb));

    rb_add(&rb, 1);
    rb_add(&rb, 2);
    rb_add(&rb, 3);
    rb_add(&rb, 4);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_FULL, er);

    ASSERT_EQ(1, rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(2, rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK, er);
    ASSERT_EQ(3, rb_get(&rb));

    // Read past the ast element
    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_NO_DATA, er);

    ASSERT_EQ(0, rb_get(&rb));
    ASSERT_EQ(0, rb_get(&rb));
    ASSERT_EQ(0, rb_get(&rb));

    // teardown shouldn't cause a crash with a static buffer
    rb_teardown(&rb);
}


TEST(ring_buffer, test_huge_static_buffer)
{
    const size_t size = 524288; // 2^19
    STATIC_BUFFER(size,rb);

    for (size_t i = 1; i < size; i++)
    {
        rb_add(&rb, i);
    }

    for (size_t i = 0; i < size; i++)
    {
        rb_get(&rb);
    }
}

TEST(string_producer,test_static_string_producer) {
    const char * str = static_string_producer(false,(char*) "string",1); 
    EXPECT_STREQ(str,"string:1");
    
    str = static_string_producer(false,(char*)"string",2); 
    EXPECT_STREQ(str,"string:2");

    str = static_string_producer(false,(char*)"string",3); 
    EXPECT_STREQ(str,"string:3");

    str = static_string_producer(false,(char*)"string",4); 
    EXPECT_STREQ(str,"string:4");

    str = static_string_producer(false,(char*)"string",4);
    ASSERT_EQ(NULL,str);

    str = static_string_producer(true,(char*)"string",5);
    EXPECT_STREQ("string:5",str);
}